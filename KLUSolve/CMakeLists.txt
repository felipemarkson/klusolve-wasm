add_library(klusolve SHARED 
 KLUSystem.cpp
 KLUSolve.cpp)

if(WIN32)
  target_compile_options(klusolve PUBLIC "-D_USRDLL")
  target_sources(klusolve PRIVATE klusolve.def)
endif()
if(UNIX)
  set(CMAKE_C_FLAGS "-O3 -fPIC")
endif()
if(APPLE)
  set(CMAKE_C_FLAGS "-O3 -fPIC")
endif()

target_link_libraries(klusolve PRIVATE
 KLU
 AMD
 BTF
 COLAMD
 CSparse
 CZSparse)
