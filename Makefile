SUBDIRS = AMD BTF COLAMD CSparse CZSparse KLU KLUSolve KLU/Demo

.PHONY: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all
all: $(SUBDIRS)

.PHONY: clean
clean: 
ifndef windir
	find . | grep '\.o'$ | xargs rm
	find . | grep '\.a'$ | xargs rm
	find . | grep '\.so'$ | xargs rm
	find . | grep ‘\.dylib’$ | xargs rm
	find . | grep ‘\.exe’$ | xargs rm
else
	del /s /q *.o
	del /s /q *.a
	del /s /q *.dll
	del /s /q *.exe
endif
