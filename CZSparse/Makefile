LIB=../.lib/czsparse.a

SRC = \
 Source/csz_stuff.c

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
