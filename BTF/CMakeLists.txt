add_library(BTF 
 Source/btf_maxtrans.c
 Source/btf_order.c
 Source/btf_strongcomp.c)

target_include_directories(BTF PRIVATE Include)