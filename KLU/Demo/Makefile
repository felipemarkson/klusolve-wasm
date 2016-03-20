EXE=../../.test/KLDemo.exe

SRC = \
 klu_simple.c

OBJ=$(SRC:.c=.o)

ifndef windir
RM=rm
else
RM=del
endif

CC=gcc
CFLAGS=-Wall -O3 -DREAD_KUNDERT -I../../Include
LDFLAGS=-L../../.lib -Bstatic -lklu -lamd -lbtf -lcolamd -lcsparse -lczsparse -lm

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : all
all : $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

.PHONY : clean
clean:
	-$(RM) $(OBJ)
