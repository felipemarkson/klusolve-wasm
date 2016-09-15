LIB=../Lib/libamd.so

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

ifndef windir
RM=rm
CFLAGS=-Wall -O3 -fPIC -arch i386 -arch x86_64 -IInclude -I../Include
else
RM=del
CFLAGS=-Wall -O3 -static -IInclude -I../Include
endif

CC=gcc

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : all
all : $(OBJ)

$(LIB): $(OBJ)
	gcc -shared -o $@ $^

.PHONY : clean
clean:
	-$(RM) $(OBJ)
