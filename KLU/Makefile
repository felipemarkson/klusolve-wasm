LIB=../.lib/libklu.a

SRC = \
 Source/klu.c \
 Source/klu_analyze.c \
 Source/klu_analyze_given.c \
 Source/klu_defaults.c \
 Source/klu_diagnostics.c \
 Source/klu_dump.c \
 Source/klu_extract.c \
 Source/klu_factor.c \
 Source/klu_free_numeric.c \
 Source/klu_free_symbolic.c \
 Source/klu_kernel.c \
 Source/klu_memory.c \
 Source/klu_refactor.c \
 Source/klu_scale.c \
 Source/klu_solve.c \
 Source/klu_sort.c \
 Source/klu_tsolve.c \
 Source/klu_z_stuff.c

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
