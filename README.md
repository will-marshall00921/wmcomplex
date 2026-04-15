# wmcomplex
## About

  wmcomplex is a lightweight C++ complex value library designed around SIMD
  operations.

  Author: Will Marshall

## Build

  CMake (>3.14) is required to build the library. In the project root directory,

  > \$ cmake -S . -B build \<BUILD OPTIONS>  
  > \$ cmake --build build --target install

## Build Options

Option     | Description                     | Default | Dependencies
-----------|---------------------------------|---------|--------------
STATIC_LIB | Build as a static library       | OFF     | --
WITH_DOCS  | Build the Doxygen documentation | ON      | Doxygen
