SUBDIRS = AMD BTF COLAMD CSparse CZSparse KLU KLU/Demo KLUSolve

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
else
	del /s /q *.o
	del /s /q *.a
	del /s /q *.dll
endif
