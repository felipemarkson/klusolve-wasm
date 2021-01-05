add_library(KLUSolve SHARED 
 KLUSystem.cpp
 KLUSolve.cpp)

if(WIN32)
  target_compile_options(KLUSolve PUBLIC "-D_USRDLL")
  target_sources(KLUSolve PRIVATE klusolve.def)
endif()
if(UNIX)
  set(CMAKE_C_FLAGS "-O3 -fPIC")
endif()
if(APPLE)
  set(CMAKE_C_FLAGS "-O3 -fPIC")
endif()

target_link_libraries(KLUSolve PRIVATE
 AMD
 BTF
 COLAMD
 CSparse
 CZSparse
 KLU)