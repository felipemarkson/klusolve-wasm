#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "KLUSolve.h"

#define COMPLEX_FMT_POSITIVE "%.2f + j %.2f\n"
#define COMPLEX_FMT_NEGATIVE "%.2f - j %.2f\n"

#define ERR_NULLPOINTER_MSG "NULL pointer error"

void print_complex(complex* a);
PTR_API create_matrix();

int main(int argc, char* argv[]) {
    PTR_API matrix = create_matrix();

    complex x[2] = {{1.0, 0.0}, {0.0, 1.0}};
    complex b[2] = {{1.0, 0.0}, {0.0, 1.0}};

    SolveSparseSet(matrix, &(x[0]), &(b[0]));

    print_complex(&(x[0]));
    print_complex(&(x[1]));
    DeleteSparseSet(matrix);

    return EXIT_SUCCESS;
}

PTR_API create_matrix() {
    PTR_API hSparse = NewSparseSet(2);
    complex a_11 = {1.0, -1.0};
    complex a_22 = {-1.0, 1.0};
    AddMatrixElement(hSparse, 1, 1, &a_11);
    AddMatrixElement(hSparse, 2, 2, &a_22);

    return hSparse;
}
void print_complex(complex* a) {
    if (a->y >= 0) {
        printf(COMPLEX_FMT_POSITIVE, a->x, a->y);
    } else {
        printf(COMPLEX_FMT_NEGATIVE, a->x, -(a->y));
    }
}