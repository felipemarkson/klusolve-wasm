/* klu_simple: a simple KLU demo */

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "klu.h"

#ifdef WIN32

#include <windows.h>

void vminfo (unsigned long *free, unsigned long *reserved, unsigned long *committed) {
    MEMORY_BASIC_INFORMATION memory_info;
    memory_info.BaseAddress = 0;
    *free = *reserved = *committed = 0;
    while (VirtualQuery (memory_info.BaseAddress, &memory_info, sizeof (memory_info))) {
        switch (memory_info.State) {
        case MEM_FREE:
            *free += (unsigned long) memory_info.RegionSize;
            break;
        case MEM_RESERVE:
            *reserved += (unsigned long) memory_info.RegionSize;
            break;
        case MEM_COMMIT:
            *committed += (unsigned long) memory_info.RegionSize;
            break;
        }
        memory_info.BaseAddress = (char *) memory_info.BaseAddress + memory_info.RegionSize;
    }
}

int cpuinfo (int whole, __int64 *kernel, __int64 *user) {
    if (whole) {
        __int64 creation64, exit64, kernel64, user64;
        int rc = GetProcessTimes (GetCurrentProcess (), 
                                  (FILETIME *) &creation64,  
                                  (FILETIME *) &exit64, 
                                  (FILETIME *) &kernel64, 
                                  (FILETIME *) &user64);
        if (! rc) {
            *kernel = 0;
            *user = 0;
            return FALSE;
        } 
        *kernel = kernel64;
        *user = user64;
        return TRUE;
    } else {
        __int64 creation64, exit64, kernel64, user64;
        int rc = GetThreadTimes (GetCurrentThread (), 
                                 (FILETIME *) &creation64,  
                                 (FILETIME *) &exit64, 
                                 (FILETIME *) &kernel64, 
                                 (FILETIME *) &user64);
        if (! rc) {
            *kernel = 0;
            *user = 0;
            return FALSE;
        } 
        *kernel = kernel64;
        *user = user64;
        return TRUE;
    }
}

unsigned long VMKiloBytes (void)
{
	unsigned long free = 0, reserved = 0, committed = 0;
	vminfo (&free, &reserved, &committed);
	return committed / 1000;
}

double Time (void)
{
	int whole = 1, ret;
	__int64 user = 0, kernel = 0;

	ret = cpuinfo (whole, &kernel, &user);
	return ((double) (kernel + user) / 10000000);
}

/* end of WIN32 stuff */
#endif

/* choose the UF simple demo, or to read Kundert's matrices */
/* #define READ_KUNDERT - do this as a compiler -D option */

#ifndef READ_KUNDERT

int    n = 5 ;
int    Ap [ ] = {0, 2, 5, 9, 10, 12} ;
int    Ai [ ] = { 0,  1,  0,   2,  4,  1,  2,  3,   4,  2,  1,  4} ;
double Ax [ ] = {2., 3., 3., -1., 4., 4., -3., 1., 2., 2., 6., 1.} ;
double b [ ] = {8., 45., -3., 3., 19.} ;

int main (void)
{
    klu_symbolic *Symbolic ;
    klu_numeric *Numeric ;
    klu_common Common ;
    int i ;
    klu_defaults (&Common) ;
    Symbolic = klu_analyze (n, Ap, Ai, &Common) ;
    Numeric = klu_factor (Ap, Ai, Ax, Symbolic, &Common) ;
    klu_solve (Symbolic, Numeric, 5, 1, b, &Common) ;
    klu_free_symbolic (&Symbolic, &Common) ;
    klu_free_numeric (&Numeric, &Common) ;
    for (i = 0 ; i < n ; i++) printf ("x [%d] = %g\n", i, b [i]) ;
    return (0) ;
}

#else  /* READ_KUNDERT */

/* ========================================================================== */
/* === copy and modify from KLU DEMO ======================================== */
/* ========================================================================== */

/* for handling complex matrices */
#define REAL(X,i) (X [2*(i)])
#define IMAG(X,i) (X [2*(i)+1])
#define CABS(X,i) (sqrt (REAL (X,i) * REAL (X,i) + IMAG (X,i) * IMAG (X,i)))

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

static int klu_backslash    /* return 1 if successful, 0 otherwise */
(
    /* --- input ---- */
    int n,		/* A is n-by-n */
    int *Ap,		/* size n+1, column pointers */
    int *Ai,		/* size nz = Ap [n], row indices */
    double *Ax,		/* size nz, numerical values */
    int isreal,		/* nonzero if A is real, 0 otherwise */
    double *B,		/* size n, right-hand-side */

    /* --- output ---- */
    double *X,		/* size n, solution to Ax=b */
    double *R,		/* size n, residual r = b-A*x */

    /* --- scalar output --- */
    int *lunz,		/* nnz (L+U+F) */
    double *rnorm,	/* norm (b-A*x,1) / norm (A,1) */

    /* --- workspace - */

    klu_common *Common	/* default parameters and statistics */
)

{
    double anorm = 0, asum ;
    klu_symbolic *Symbolic ;
    klu_numeric *Numeric ;
    int i, j, p ;

    if (!Ap || !Ai || !Ax || !B || !X || !B) return (0) ;

    /* ---------------------------------------------------------------------- */
    /* symbolic ordering and analysis */
    /* ---------------------------------------------------------------------- */

    Symbolic = klu_analyze (n, Ap, Ai, Common) ;
    if (!Symbolic) return (0) ;

    if (isreal)
    {

	/* ------------------------------------------------------------------ */
	/* factorization */
	/* ------------------------------------------------------------------ */

	Numeric = klu_factor (Ap, Ai, Ax, Symbolic, Common) ;
	if (!Numeric)
	{
	    klu_free_symbolic (&Symbolic, Common) ;
	    return (0) ;
	}

	/* ------------------------------------------------------------------ */
	/* statistics (not required to solve Ax=b) */
	/* ------------------------------------------------------------------ */

	klu_rgrowth (Ap, Ai, Ax, Symbolic, Numeric, Common) ;
	if (n > 1) klu_condest (Ap, Ax, Symbolic, Numeric, Common) ;
	klu_rcond (Symbolic, Numeric, Common) ;
	klu_flops (Symbolic, Numeric, Common) ;
	*lunz = Numeric->lnz + Numeric->unz - n + 
	    ((Numeric->Offp) ? (Numeric->Offp [n]) : 0) ;

	/* ------------------------------------------------------------------ */
	/* solve Ax=b */
	/* ------------------------------------------------------------------ */

	for (i = 0 ; i < n ; i++)
	{
	    X [i] = B [i] ;
	}
	klu_solve (Symbolic, Numeric, n, 1, X, Common) ;

	/* ------------------------------------------------------------------ */
	/* compute residual, rnorm = norm(b-Ax,1) / norm(A,1) */
	/* ------------------------------------------------------------------ */

	for (i = 0 ; i < n ; i++)
	{
	    R [i] = B [i] ;
	}
	for (j = 0 ; j < n ; j++)
	{
	    asum = 0 ;
	    for (p = Ap [j] ; p < Ap [j+1] ; p++)
	    {
		/* R (i) -= A (i,j) * X (j) */
		R [Ai [p]] -= Ax [p] * X [j] ;
		asum += fabs (Ax [p]) ;
	    }
	    anorm = MAX (anorm, asum) ;
	}
	*rnorm = 0 ;
	for (i = 0 ; i < n ; i++)
	{
	    *rnorm = MAX (*rnorm, fabs (R [i])) ;
	}

	/* ------------------------------------------------------------------ */
	/* free numeric factorization */
	/* ------------------------------------------------------------------ */

	klu_free_numeric (&Numeric, Common) ;

    }
    else
    {

	/* ------------------------------------------------------------------ */
	/* statistics (not required to solve Ax=b) */
	/* ------------------------------------------------------------------ */

	Numeric = klu_z_factor (Ap, Ai, Ax, Symbolic, Common) ;
	if (!Numeric)
	{
	    klu_free_symbolic (&Symbolic, Common) ;
	    return (0) ;
	}

	/* ------------------------------------------------------------------ */
	/* statistics */
	/* ------------------------------------------------------------------ */

	klu_z_rgrowth (Ap, Ai, Ax, Symbolic, Numeric, Common) ;
	if (n > 1) klu_z_condest (Ap, Ax, Symbolic, Numeric, Common) ;
	klu_z_rcond (Symbolic, Numeric, Common) ;
	klu_z_flops (Symbolic, Numeric, Common) ;
	*lunz = Numeric->lnz + Numeric->unz - n + 
	    ((Numeric->Offp) ? (Numeric->Offp [n]) : 0) ;

	/* ------------------------------------------------------------------ */
	/* solve Ax=b */
	/* ------------------------------------------------------------------ */

	for (i = 0 ; i < 2*n ; i++)
	{
	    X [i] = B [i] ;
	}
	klu_z_solve (Symbolic, Numeric, n, 1, X, Common) ;

	/* ------------------------------------------------------------------ */
	/* compute residual, rnorm = norm(b-Ax,1) / norm(A,1) */
	/* ------------------------------------------------------------------ */

	for (i = 0 ; i < 2*n ; i++)
	{
	    R [i] = B [i] ;
	}
	for (j = 0 ; j < n ; j++)
	{
	    asum = 0 ;
	    for (p = Ap [j] ; p < Ap [j+1] ; p++)
	    {
		/* R (i) -= A (i,j) * X (j) */
		i = Ai [p] ;
		REAL (R,i) -= REAL(Ax,p) * REAL(X,j) - IMAG(Ax,p) * IMAG(X,j) ;
		IMAG (R,i) -= IMAG(Ax,p) * REAL(X,j) + REAL(Ax,p) * IMAG(X,j) ;
		asum += CABS (Ax, p) ;
	    }
	    anorm = MAX (anorm, asum) ;
	}
	*rnorm = 0 ;
	for (i = 0 ; i < n ; i++)
	{
	    *rnorm = MAX (*rnorm, CABS (R, i)) ;
	}

	/* ------------------------------------------------------------------ */
	/* free numeric factorization */
	/* ------------------------------------------------------------------ */

	klu_z_free_numeric (&Numeric, Common) ;
    }

    /* ---------------------------------------------------------------------- */
    /* free symbolic analysis, and residual */
    /* ---------------------------------------------------------------------- */

    klu_free_symbolic (&Symbolic, Common) ;
    return (1) ;
}


/* ========================================================================== */
/* === klu_demo ============================================================= */
/* ========================================================================== */

/* Given a sparse matrix A, set up a right-hand-side and solve X = A\b */
/* TODO - input the right-hand side */

static void klu_demo (int n, int *Ap, int *Ai, double *Ax, double *rhs, int isreal)
{
    double rnorm ;
    klu_common Common ;
    double *B, *X, *R ;
    int i, lunz ;

    printf ("KLU: %s, version: %d.%d.%d\n", KLU_DATE, KLU_MAIN_VERSION,
	KLU_SUB_VERSION, KLU_SUBSUB_VERSION) ;

    /* ---------------------------------------------------------------------- */
    /* set defaults */
    /* ---------------------------------------------------------------------- */

    klu_defaults (&Common);

    /* ---------------------------------------------------------------------- */
    /* create a right-hand-side */
    /* ---------------------------------------------------------------------- */

    if (isreal) {
		/* B = 1 + (1:n)/n */
		B = klu_malloc (n, sizeof (double), &Common);
		X = klu_malloc (n, sizeof (double), &Common);
		R = klu_malloc (n, sizeof (double), &Common);
		if (B) {
			for (i = 0 ; i < n ; i++) {
				B [i] = 1 + ((double) i+1) / ((double) n);
			}
		}
    } else {
		/* real (B) = 1 + (1:n)/n, imag(B) = (n:-1:1)/n */
		B = klu_malloc (n, 2 * sizeof (double), &Common);
		X = klu_malloc (n, 2 * sizeof (double), &Common);
		R = klu_malloc (n, 2 * sizeof (double), &Common);
		if (B) {
			for (i = 0 ; i < n ; i++) {
				REAL (B, i) = 1 + ((double) i+1) / ((double) n);
				IMAG (B, i) = ((double) n-i) / ((double) n);
			}
		}
    }

    /* ---------------------------------------------------------------------- */
    /* X = A\b using KLU and print statistics */
    /* ---------------------------------------------------------------------- */

    if (!klu_backslash (n, Ap, Ai, Ax, isreal, B, X, R, &lunz, &rnorm, &Common)) {
		printf ("KLU failed\n");
    } else {
		printf ("n %d nnz(A) %d nnz(L+U+F) %d resid %g\n"
			"recip growth %g condest %g rcond %g flops %g\n",
			n, Ap [n], lunz, rnorm, Common.rgrowth, Common.condest,
			Common.rcond, Common.flops);
    }

    /* ---------------------------------------------------------------------- */
    /* free the problem */
    /* ---------------------------------------------------------------------- */

    if (isreal) {
		klu_free (B, n, sizeof (double), &Common);
		klu_free (X, n, sizeof (double), &Common);
		klu_free (R, n, sizeof (double), &Common);
    } else {
		klu_free (B, 2*n, sizeof (double), &Common);
		klu_free (X, 2*n, sizeof (double), &Common);
		klu_free (R, 2*n, sizeof (double), &Common);
    }
    printf ("peak memory usage: %g bytes\n\n", (double) (Common.mempeak));
}

#include "cs.h"
#include "csz.h"

int usage ()
{
	printf ("usage: klDemo filename\n");
	return 1;
}

// #define BUFSIZ 1024

int get_kundert_header (FILE *fp, int *isreal, int *ndim)
{
	char msg[BUFSIZ], tok [BUFSIZ];
	int nTok;
	*isreal = -1;
	*ndim = -1;

    if (NULL == fgets (msg, BUFSIZ, fp)) {
		fprintf (stderr, "kundert hdr 1\n");
        return 0;
    }

	/* For compatibility with the old file syntax. */
    if (!strnicmp( msg, "Starting", 8)) {
		if (strnicmp( msg, "Starting complex", 15 ) == 0) {
			*isreal = 0;
		} else {
			*isreal = 1;
		}
        if (NULL == fgets (msg, BUFSIZ, fp)) {
			fprintf (stderr, "kundert hdr 2\n");
            return 0;
        }
    }

	/* Read size and type of matrix. */
    if (NULL == fgets (msg, BUFSIZ, fp)) {   
		fprintf (stderr, "kundert hdr 3\n");
        return 0;
    }
    if ((nTok = sscanf (msg,"%d %s", ndim, tok)) < 1) {   
		fprintf (stderr, "kundert hdr 4\n");
        return 0;
    }
    if (nTok == 2) {  /* new format has the type in second token */
		if (strnicmp (tok, "complex", 7 ) == 0) {
			*isreal = 0;
		} else if (strnicmp (tok, "real", 4) == 0) {
			*isreal = 1;
		} else {   
			fprintf (stderr, "kundert hdr 5\n");
            return 0;
        }
    }

	return 1;
}

/* build the matrix transposed if using cs_transpose later to sort the columns */
int read_kundert_values (FILE *fp, cs *triplet, int isreal, int transpose)
{
	char msg[BUFSIZ];
	int i, j, nTok;
	double re, im;
	long ln = 0L;

	do {
		if (NULL == fgets (msg, BUFSIZ, fp)) {
			fprintf (stderr, "kundert val missing\n");
			return 0;
		}
		if (isreal) {
			nTok = sscanf (msg,"%d%d%lf", &i, &j, &re);
			if (nTok != 3) {
				fprintf (stderr, "kundert val incomplete at %s\n", msg);
				return 0;
			}
		} else {
			nTok = sscanf (msg,"%d%d%lf%lf", &i, &j, &re, &im);
			if (nTok != 4) {
				fprintf (stderr, "kundert val incomplete at %s\n", msg);
				return 0;
			}
		}
		if (i < 0 || j < 0) {
			fprintf (stderr, "kundert val negative indices at %s\n", msg);
			return 0;
		}
		if (i > 0 && j > 0) {
			if (isreal) {
				if (transpose) {
					cs_entry (triplet, j-1, i-1, re);
				} else {
					cs_entry (triplet, i-1, j-1, re);
				}
			} else {
				if (transpose) {
					csz_entry (triplet, j-1, i-1, re, im);
				} else {
					csz_entry (triplet, i-1, j-1, re, im);
				}
			}
		}
		++ln;
	} while (i != 0 && j != 0);

	return 1;
}

/* if no source vector, we are supposed to use the first column of A; return -1 */
int read_kundert_source (FILE *fp, double *rhs, int n, int isreal)
{
	char msg[BUFSIZ];
	int i, j, nTok;
	double re, im;
	int iMissing = 0;

	/* read the first source line */
	if (NULL == fgets (msg, BUFSIZ, fp)) {
		fprintf (stderr, "kundert src missing, will use 1st column of A\n");
		fprintf (stdout, "kundert src missing, will use 1st column of A\n");
		return -1;
	}
	if (strnicmp (msg, "Beginning", 9) == 0) { /* old format, read the next one */
		if (NULL == fgets (msg, BUFSIZ, fp)) {
			fprintf (stderr, "kundert src missing, will use 1st column of A\n");
			fprintf (stdout, "kundert src missing, will use 1st column of A\n");
			return -1;
		}
	}

	j = 0;
	for (i = 0; i < n; i++) {
		if (i > 0) {
			if (NULL == fgets (msg, BUFSIZ, fp)) {
				fprintf (stderr, "kundert src missing 3 at %d\n", i);
				return 0;
			}
		}
		if (isreal) {
			nTok = sscanf (msg, "%lf", &re);
			rhs[j++] = re;
		} else {
			nTok = sscanf (msg, "%lf%lf", &re, &im);
			rhs[j++] = re;
			rhs[j++] = im;
		}
	}

	return 1;
}

int main (int argc, char *argv[])
{
	int n, isreal, i, p, sort_columns;
	int *Ap = NULL, *Ai = NULL;
	double *Ax = NULL, *rhs = NULL;
	FILE *fp = NULL;
	cs *triplet = NULL, *compress = NULL, *A = NULL;
	klu_symbolic *Symbolic;
    klu_numeric *Numeric;
    klu_common Common;
	int lunz;
	double rnorm;
//	unsigned long kbStart, kbEnd;
	double BeginTime;

	sort_columns = 1;

    BeginTime = Time();
//	kbStart = VMKiloBytes();

	/* load a matrix in triplet form */
	if (argc != 2) {
		return usage();
	}
	fp = fopen (argv[1], "r");
	if (!fp) {
		printf ("failed to open '%s' for read\n", argv[1]);
		return 0;
	}

	get_kundert_header (fp, &isreal, &n);

	if (n < 1) {
		printf ("matrix dimension must be positive\n");
		return 0;
	}

	/* read the values */
	if (isreal) {
		triplet = cs_spalloc (n, n, n, 1, 1);
	} else {
		triplet = csz_spalloc (n, n, n, 1, 1);
	}
	read_kundert_values (fp, triplet, isreal, sort_columns ? 1 : 0);

	/* put into compressed column format */
	if (isreal) {
		compress = cs_compress (triplet);
		cs_dupl (compress);
		cs_dropzeros (compress);
		if (sort_columns) {
			A = cs_transpose (compress, 1);
			cs_spfree (compress);
		} else {
			A = compress;
		}
//		cs_print (triplet, 0);
//		cs_print (A, 0);
	} else {
		compress = csz_compress (triplet);
		csz_dupl (compress);
		csz_dropzeros (compress);
		if (sort_columns) {
			A = csz_transpose (compress, 1);
			cs_spfree (compress);
		} else {
			A = compress;
		}
//		csz_print (triplet, 0);
//		csz_print (A, 0);
	}

	cs_spfree (triplet);
	n = A->n;
	Ap = A->p;
	Ai = A->i;
	Ax = A->x;

	/* read the RHS, but pre-load the default value as 1st column from A */
	if (isreal) {
		rhs = cs_malloc (n, sizeof (double));
		for (i = 0; i < n; i++) rhs[i] = 0.0;
		for (p = Ap[0]; p < Ap[1]; p++) {
			i = Ai[p];
			rhs[i] = Ax[p];
		}
	} else {
		rhs = cs_malloc (2 * n, sizeof (double));
		for (i = 0; i < 2 * n; i++) rhs[i] = 0.0;
		for (p = Ap[0]; p < Ap[1]; p++) {
			i = Ai[p];
			rhs[2*i] = Ax[2*p];
			rhs[2*i + 1] = Ax[2*p + 1];
		}
	}
	read_kundert_source (fp, rhs, n, isreal);

	/* solve it */
	rnorm = 0.0;
	klu_defaults (&Common);
	Common.halt_if_singular = 0; // only for testing
    Symbolic = klu_analyze (n, Ap, Ai, &Common);
	if (isreal) {
	    Numeric = klu_factor (Ap, Ai, Ax, Symbolic, &Common);
		klu_solve (Symbolic, Numeric, n, 1, rhs, &Common);

		klu_rgrowth (Ap, Ai, Ax, Symbolic, Numeric, &Common);
		if (n > 1) klu_condest (Ap, Ax, Symbolic, Numeric, &Common);
		klu_rcond (Symbolic, Numeric, &Common);
		klu_flops (Symbolic, Numeric, &Common);
		lunz = Numeric->lnz + Numeric->unz - n + 
			((Numeric->Offp) ? (Numeric->Offp [n]) : 0);
		printf ("n %d nnz(A) %d nnz(L+U+F) %d resid %g\n"
			"recip growth %g condest %g rcond %g flops %g\n",
			n, Ap [n], lunz, rnorm, Common.rgrowth, Common.condest,
			Common.rcond, Common.flops);

	    klu_free_numeric (&Numeric, &Common);
	} else {
	    Numeric = klu_z_factor (Ap, Ai, Ax, Symbolic, &Common);
		klu_z_solve (Symbolic, Numeric, n, 1, rhs, &Common);

		klu_z_rgrowth (Ap, Ai, Ax, Symbolic, Numeric, &Common);
		if (n > 1) klu_z_condest (Ap, Ax, Symbolic, Numeric, &Common);
		klu_z_rcond (Symbolic, Numeric, &Common);
		klu_z_flops (Symbolic, Numeric, &Common);
		lunz = Numeric->lnz + Numeric->unz - n + 
			((Numeric->Offp) ? (Numeric->Offp [n]) : 0);
		printf ("n %d nnz(A) %d nnz(L+U+F) %d resid %g\n"
			"recip growth %g condest %g rcond %g flops %g\n",
			n, Ap [n], lunz, rnorm, Common.rgrowth, Common.condest,
			Common.rcond, Common.flops);

		klu_z_free_numeric (&Numeric, &Common);
	}
    klu_free_symbolic (&Symbolic, &Common);

	for (i = 0 ; i < n && i <= 10 ; i++) {
		if (isreal) {
			printf ("x [%d] = %g\n", i, rhs[i]);
		} else {
			printf ("x [%d] = %g + j%g\n", i, rhs[2*i], rhs[2*i+1]);
		}
	}

	if (rhs) {
		cs_free (rhs);
	}
	cs_spfree (A);

//	kbEnd = VMKiloBytes();
	printf ("\nAggregate resource usage:\n");
    printf ("    Time required = %.2f seconds.\n", Time() - BeginTime);
//    printf ("    Virtual memory used = %ul kBytes.\n", kbEnd - kbStart);
    printf ("    Peak memory usage: %ul kBytes.\n", Common.mempeak / 1000);

	return (0) ;
}

#endif