FILES=KLUSolve KLUSystem
OBJ=$(addsuffix .o,$(FILES))
DLL=../Lib/libklusolve.dll
LIB=../Lib/libklusolve.a
SO=../Lib/libklusolve.dylib

ifndef WINDIR
uname_S := $(shell uname -s)
else
uname_S := Windows
endif

ifeq ($(uname_S),Darwin)
RM=rm
CC=g++
CFLAGS=-c -Wall -O3 -fPIC -arch i386 -arch x86_64 -I../Include
LDFLAGS=-L../Lib -lstdc++
.PHONY : all
all : $(SO)
$(SO): $(OBJ)
	cp ../AMD/Source/*.o Obj
	cp ../BTF/Source/*.o Obj
	cp ../COLAMD/Source/*.o Obj
	cp ../CSparse/Source/*.o Obj
	cp ../CZSparse/Source/*.o Obj
	cp ../KLU/Source/*.o Obj
	sleep 2
	gcc -dynamiclib -fPIC -arch i386 -arch x86_64 $^ $(wildcard Obj/*.o) $(LDFLAGS) -o $@
$(OBJ): %.o : %.cpp %.h
	$(CC) $(CFLAGS) $< -o $@
endif

ifeq ($(uname_S),Linux)
RM=rm
CC=g++
CFLAGS=-c -Wall -O3 -fPIC -I../Include
LDFLAGS=-L../Lib -Bstatic -lklu -lamd -lbtf -lcolamd -lczsparse -lcsparse -lstdc++
ARCHIVES=libklu.a libamd.a libbtf.a libcolamd.a libczsparse.a libcsparse.a
ARSCRIPT=script.ar
ADIR=../Lib
.PHONY : all
all : $(LIB)
$(LIB): $(OBJ)
	$(SILENT)echo "CREATE $@" > $(ARSCRIPT)
	$(SILENT)for a in $(ARCHIVES); do (echo "ADDLIB $(ADIR)/$$a" >> $(ARSCRIPT)); done
	$(SILENT)echo "ADDMOD $(OBJ)" >> $(ARSCRIPT)
	$(SILENT)echo "SAVE" >> $(ARSCRIPT)
	$(SILENT)echo "END" >> $(ARSCRIPT)
	$(SILENT)$(AR) -M < $(ARSCRIPT)
$(OBJ): %.o : %.cpp %.h
	$(CC) $(CFLAGS) $< -o $@
endif

ifeq ($(uname_S),Windows)
RM=rm
CC=g++
CFLAGS=-c -Wall -O3 -DWIN32 -DNDEBUG -D_WINDOWS -DKLUSOLVE_EXPORTS -I../Include
LDFLAGS=-L../Lib -Bstatic -lklu -lamd -lbtf -lcolamd -lczsparse -lcsparse -lstdc++
ARCHIVES=libklu.a libamd.a libbtf.a libcolamd.a libczsparse.a libcsparse.a
ARSCRIPT=script.ar
ADIR=../Lib
.PHONY : all
all : $(DLL)
$(DLL): $(OBJ)
	gcc -shared $^ $(LDFLAGS) -o $@ -Wl,--out-implib,$(LIB)
$(LIB): $(OBJ)
	$(SILENT)echo "CREATE $@" > $(ARSCRIPT)
	$(SILENT)echo "ADDLIB ../Lib/libklu.a" >> $(ARSCRIPT)
	$(SILENT)echo "ADDLIB ../Lib/libamd.a" >> $(ARSCRIPT)
	$(SILENT)echo "ADDLIB ../Lib/libbtf.a" >> $(ARSCRIPT)
	$(SILENT)echo "ADDLIB ../Lib/libcolamd.a" >> $(ARSCRIPT)
	$(SILENT)echo "ADDLIB ../Lib/libczsparse.a" >> $(ARSCRIPT)
	$(SILENT)echo "ADDLIB ../Lib/libcsparse.a" >> $(ARSCRIPT)
	$(SILENT)echo "ADDMOD $(OBJ)" >> $(ARSCRIPT)
	$(SILENT)echo "SAVE" >> $(ARSCRIPT)
	$(SILENT)echo "END" >> $(ARSCRIPT)
	$(SILENT)$(AR) -M < $(ARSCRIPT)
$(OBJ): %.o : %.cpp %.h
	$(CC) $(CFLAGS) $< -o $@
endif

.PHONY : clean
clean:
	-$(RM) $(OBJ)


