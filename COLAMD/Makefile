LIB=../.lib/libcolamd.a

SRC = \
 Source/colamd.c \
 Source/colamd_global.c

OBJ=$(SRC:.c=.o)

ifndef windir
RM=rm
else
RM=del
endif

CC=gcc
CFLAGS=-Wall -O3 -fPIC -static -IInclude -I../Include

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : all
all : $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

.PHONY : clean
clean:
	-$(RM) $(OBJ)
