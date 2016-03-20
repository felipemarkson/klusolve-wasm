FILES=KLUSolve KLUSystem
OBJ=$(addsuffix .o,$(FILES))
DLL=../.lib/klusolve.dll
LIB=../.lib/libklusolve.a
SO=../.lib/klusolve.so

ifndef windir

RM=rm
CC=g++
CFLAGS=-c -Wall -O3 -fPIC -I../Include
LDFLAGS=-L../.lib -Bstatic -lklu -lamd -lbtf -lcolamd -lczsparse -lcsparse -lstdc++

.PHONY : all
all : $(SO)

$(SO): $(OBJ)
	gcc -shared -fPIC $^ $(LDFLAGS) -o $@

$(OBJ): %.o : %.cpp %.h
	$(CC) $(CFLAGS) $< -o $@

else

RM=del
CC=g++
CFLAGS=-c -Wall -O3 -DWIN32 -DNDEBUG -D_WINDOWS -D_USRDLL -DKLUSOLVE_EXPORTS -I../Include
LDFLAGS=-L/klusolve/.lib -Bstatic -lklu -lamd -lbtf -lcolamd -lczsparse -lcsparse -lstdc++

.PHONY : all
all : $(DLL)

$(DLL): $(OBJ)
	gcc -shared $^ $(LDFLAGS) -o $@ -Wl,--out-implib,$(LIB)

$(OBJ): %.o : %.cpp %.h
	$(CC) $(CFLAGS) $< -o $@

endif

.PHONY : clean
clean:
	-$(RM) $(OBJ)


