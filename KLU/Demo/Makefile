EXE=../../Test/KLDemo.exe

SRC = \
 klu_simple.c

OBJ=$(SRC:.c=.o)

ifndef windir
RM=rm
else
RM=del
endif

CC=gcc
CFLAGS=-Wall -O3 -DREAD_KUNDERT -arch i386 -arch x86_64 -I../../Include
LDFLAGS=-arch i386 -L../../Lib -lklusolve -lm

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : all
all : $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

.PHONY : clean
clean:
	-$(RM) $(OBJ)
