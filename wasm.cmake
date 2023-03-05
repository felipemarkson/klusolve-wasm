if(EMSCRIPTEN)
  set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)
  set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "-s SIDE_MODULE=1")
  set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "-s SIDE_MODULE=1")
  set(CMAKE_STRIP FALSE)  # used by default in pybind11 on .so modules
  
  # link with -O3 for metadce and other powerful optimizations. note that we
  # must use add_link_options so that this appears after CMake's default -O2
  add_link_options("-O3")
  # add_link_flag("-s SINGLE_FILE")
  # add_link_flag("-s ALLOW_MEMORY_GROWTH=1")
  # add_compile_flag("-s DISABLE_EXCEPTION_CATCHING=0")
  # add_link_flag("-s DISABLE_EXCEPTION_CATCHING=0")
  # make the tools immediately usable on Node.js
  # add_link_flag("-s NODERAWFS")
  # in opt builds, LTO helps so much (>20%) it's worth slow compile times
  # add_nondebug_compile_flag("-flto")
endif()

