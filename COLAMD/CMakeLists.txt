add_library(COLAMD
 Source/colamd.c
 Source/colamd_global.c)

target_include_directories(COLAMD PRIVATE Include)