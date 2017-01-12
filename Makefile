SUBDIRS = AMD BTF COLAMD CSparse CZSparse KLU KLUSolve KLU/Demo

.PHONY: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all
all: $(SUBDIRS)

.PHONY: clean
clean: 
ifndef windir
	find . | grep '\.o'$ | xargs rm -f
	find . | grep '\.a'$ | xargs rm -f
	find . | grep '\.so'$ | xargs rm -f
	find . | grep '\.dylib'$ | xargs rm -f
	find . | grep '\.exe'$ | xargs rm -f
	find . | grep '\.dll'$ | xargs rm -f
else
	del /s /q *.o
	del /s /q *.a
	del /s /q *.dll
	del /s /q *.exe
endif
