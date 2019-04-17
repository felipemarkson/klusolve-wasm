LIB=../Lib/libklu.a

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

ifndef WINDIR
uname_S := $(shell uname -s)
else
uname_S := Windows
endif

ifeq ($(uname_S),Darwin)
RM=rm
CFLAGS=-Wall -O3 -fPIC -arch x86_64 -IInclude -I../Include
.PHONY : all
all : $(OBJ)
endif

ifeq ($(uname_S),Linux)
RM=rm
CFLAGS=-Wall -O3 -fPIC -static -IInclude -I../Include
.PHONY : all
all : $(LIB)
$(LIB): $(OBJ)
	ar rcs $@ $^
endif

ifeq ($(uname_S),Windows)
RM=rm
CFLAGS=-Wall -O3 -static -IInclude -I../Include
.PHONY : all
all : $(LIB)
$(LIB): $(OBJ)
	ar rcs $@ $^
endif

CC=gcc

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : clean
clean:
	-$(RM) $(OBJ)
