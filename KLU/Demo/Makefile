EXE=KLDemo.exe
EXE=../../Test/KLDemo.exe

SRC = \
 klu_simple.c

OBJ=$(SRC:.c=.o)

ifndef WINDIR
uname_S := $(shell uname -s)
else
uname_S := Windows
endif

ifeq ($(uname_S),Darwin)
RM=rm
CFLAGS=-Wall -O3 -DREAD_KUNDERT -arch i386 -arch x86_64 -I../../Include
LDFLAGS=-arch i386 -L../../Lib -lklusolve -lm
endif

ifeq ($(uname_S),Linux)
RM=rm
CFLAGS=-Wall -O3 -DREAD_KUNDERT -I../../Include
LDFLAGS=-L../../Lib -Bstatic -lklu -lamd -lbtf -lcolamd -lcsparse -lczsparse -lm
endif

ifeq ($(uname_S),Windows)
RM=rm
CFLAGS=-Wall -O3 -I../../Include
CFLAGS=-Wall -O3 -DREAD_KUNDERT -I../../Include
LDFLAGS=-L../../Lib -Bstatic -lklu -lamd -lbtf -lcolamd -lcsparse -lczsparse -lm
endif

CC=gcc

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : all
all : $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

.PHONY : clean
clean:
	-$(RM) $(OBJ)
