cmake_minimum_required(VERSION 3.18)
project(KLUSolve)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(WIN32)
  set(CMAKE_C_FLAGS "/O2 -D_WINDOWS")
endif()
if(UNIX)
  set(CMAKE_C_FLAGS "-O3 -fPIC")
endif()
if(APPLE)
  set(CMAKE_C_FLAGS "-O3 -fPIC")
endif()

include_directories(Include)

# shared library for OpenDSS
add_subdirectory(AMD)
add_subdirectory(BTF)
add_subdirectory(COLAMD)
add_subdirectory(CSparse)
add_subdirectory(CZSparse)
add_subdirectory(KLU)
add_subdirectory(KLUSolve)
#install(TARGETS KLUSolve DESTINATION klu)
install(TARGETS KLUSolve DESTINATION "${CMAKE_SOURCE_DIR}/Lib")

# demonstration program for local testing
add_executable(KLDemo KLU/Demo/klu_simple.c)
target_compile_options(KLDemo PUBLIC "-DREAD_KUNDERT")
target_link_libraries(KLDemo PRIVATE
 AMD
 BTF
 COLAMD
 CSparse
 CZSparse
 KLU)
install(TARGETS KLDemo DESTINATION "${CMAKE_SOURCE_DIR}/Test")
