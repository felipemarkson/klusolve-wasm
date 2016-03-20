LIB=../.lib/libcsparse.a

SRC = \
 Source/cs_add.c \
 Source/cs_amd.c \
 Source/cs_chol.c \
 Source/cs_cholsol.c \
 Source/cs_compress.c \
 Source/cs_counts.c \
 Source/cs_cumsum.c \
 Source/cs_dfs.c \
 Source/cs_dmperm.c \
 Source/cs_droptol.c \
 Source/cs_dropzeros.c \
 Source/cs_dupl.c \
 Source/cs_entry.c \
 Source/cs_ereach.c \
 Source/cs_etree.c \
 Source/cs_fkeep.c \
 Source/cs_gaxpy.c \
 Source/cs_happly.c \
 Source/cs_house.c \
 Source/cs_ipvec.c \
 Source/cs_leaf.c \
 Source/cs_load.c \
 Source/cs_lsolve.c \
 Source/cs_ltsolve.c \
 Source/cs_lu.c \
 Source/cs_lusol.c \
 Source/cs_malloc.c \
 Source/cs_maxtrans.c \
 Source/cs_multiply.c \
 Source/cs_norm.c \
 Source/cs_permute.c \
 Source/cs_pinv.c \
 Source/cs_post.c \
 Source/cs_print.c \
 Source/cs_pvec.c \
 Source/cs_qr.c \
 Source/cs_qrsol.c \
 Source/cs_randperm.c \
 Source/cs_reach.c \
 Source/cs_scatter.c \
 Source/cs_scc.c \
 Source/cs_schol.c \
 Source/cs_spsolve.c \
 Source/cs_sqr.c \
 Source/cs_symperm.c \
 Source/cs_tdfs.c \
 Source/cs_transpose.c \
 Source/cs_updown.c \
 Source/cs_usolve.c \
 Source/cs_util.c \
 Source/cs_utsolve.c

OBJ=$(SRC:.c=.o)

ifndef windir
RM=rm
CFLAGS=-Wall -O3 -fPIC -static -IInclude -I../Include
else
RM=del
CFLAGS=-Wall -O3 -static -IInclude -I../Include
endif

CC=gcc

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : all
all : $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

.PHONY : clean
clean:
	-$(RM) $(OBJ)
