LIB=../.lib/amd.a

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

CC=gcc
CFLAGS=-Wall -O3 -static -Iinclude -I../include
RM=rm

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : all
all : $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

.PHONY : clean
clean:
	-$(RM) $(OBJ) core