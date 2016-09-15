LIB=../Lib/libcolamd.so

SRC = \
 Source/colamd.c \
 Source/colamd_global.c

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
