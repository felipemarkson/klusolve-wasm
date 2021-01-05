add_library(KLU
 Source/klu.c
 Source/klu_analyze.c
 Source/klu_analyze_given.c
 Source/klu_defaults.c
 Source/klu_diagnostics.c
 Source/klu_dump.c
 Source/klu_extract.c
 Source/klu_factor.c
 Source/klu_free_numeric.c
 Source/klu_free_symbolic.c
 Source/klu_kernel.c
 Source/klu_memory.c
 Source/klu_refactor.c
 Source/klu_scale.c
 Source/klu_solve.c
 Source/klu_sort.c
 Source/klu_tsolve.c
 Source/klu_z_stuff.c)

target_include_directories(KLU PRIVATE Include)