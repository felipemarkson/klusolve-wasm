LIB=../Lib/libczsparse.a

SRC = \
 Source/csz_stuff.c

OBJ=$(SRC:.c=.o)

ifndef WINDIR
uname_S := $(shell uname -s)
else
uname_S := Windows
endif

ifeq ($(uname_S),Darwin)
RM=rm
CFLAGS=-Wall -O3 -fPIC -arch i386 -arch x86_64 -IInclude -I../Include
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
