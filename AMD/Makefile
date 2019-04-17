LIB=../Lib/libamd.a

SRC = \
 Source/amd_1.c \
 Source/amd_2.c \
 Source/amd_aat.c \
 Source/amd_control.c \
 Source/amd_defaults.c \
 Source/amd_dump.c \
 Source/amd_global.c \
 Source/amd_info.c \
 Source/amd_order.c \
 Source/amd_post_tree.c \
 Source/amd_postorder.c \
 Source/amd_preprocess.c \
 Source/amd_valid.c

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
