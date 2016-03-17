LIB=../.lib/klusolve.dll
IMP=../.lib/libklusolve.a

FILES=klusolve klusystem

OBJ=$(addsuffix .o,$(FILES))

CC=g++
CFLAGS=-c -Wall -O3 -DWIN32 -DNDEBUG -D_WINDOWS -D_USRDLL -DKLUSOLVE_EXPORTS -I../include
LDFLAGS=-L/klusolve/.lib -Bstatic -lklu -lamd -lbtf -lcolamd -lczsparse -lcsparse -lstdc++
RM=rm

.PHONY : all
all : $(LIB)

$(LIB): $(OBJ)
	gcc -shared $^ $(LDFLAGS) -o $@ -Wl,--out-implib,$(IMP)

$(OBJ): %.o : %.cpp %.h
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean
clean:
	-$(RM) $(OBJ) core
