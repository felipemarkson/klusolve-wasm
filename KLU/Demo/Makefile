EXE=../../.test/KLDemo.exe

SRC = \
 klu_simple.c

OBJ=$(SRC:.c=.o)

CC=gcc
CFLAGS=-Wall -O3 -DREAD_KUNDERT -I../../include
LDFLAGS=-L/klusolve/.lib -Bstatic -lklu -lamd -lbtf -lcolamd -lcsparse -lczsparse
RM=rm

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : all
all : $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

.PHONY : clean
clean:
	-$(RM) $(OBJ) core
