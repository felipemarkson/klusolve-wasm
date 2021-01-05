cmake_minimum_required(VERSION 3.18)
project(KLUSolve)

set(DEFAULT_BUILD_TYPE "Release")

if(WIN32)
set(CMAKE_C_FLAGS "/O2")
endif()
if(UNIX)
set(CMAKE_C_FLAGS "-O3 -fIPC")
endif()
if(APPLE)
set(CMAKE_C_FLAGS "-O3 -fIPC")
endif()

include_directories(Include)

add_subdirectory(AMD)
add_subdirectory(BTF)
add_subdirectory(COLAMD)
add_subdirectory(CSparse)
add_subdirectory(CZSparse)
add_subdirectory(KLU)
#add_subdirectory(KLUSolve)

