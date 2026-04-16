# wmcomplex -- CMakeLists.txt
# Author: Will Marshall
# Created: 4/14/2026, 9:08:20 PM

cmake_minimum_required (VERSION 3.14)

project(WMComplex VERSION 1.1.1 LANGUAGES CXX)

################################################################################
# Configure the project

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(STATIC_LIB "Build as a static library" OFF)
option(WITH_DOCS "Build the Doxygen documentation" ON)
option(WITH_TESTS "Build tests" ON)

if (${STATIC_LIB})
  set(WMCOMPLEX_LIBRARY_TYPE STATIC)
else()
  set(WMCOMPLEX_LIBRARY_TYPE SHARED)
endif()

configure_file(
  "cmake/complex.config.hpp.in"
  "${CMAKE_SOURCE_DIR}/include/wm/complex/config.hpp"
  @ONLY
)

################################################################################
# Build the project

add_library(wmcomplex
  ${WMCOMPLEX_LIBRARY_TYPE}
  "src/complex.cpp"
  "src/multiops.cpp"
)

if(NOT MSVC)
    target_compile_options(wmcomplex PRIVATE -march=native)
else()
 target_compile_options(wmcomplex PRIVATE /arch:AVX2)
endif()

if(NOT ${STATIC_LIB})
  target_compile_definitions(wmcomplex PRIVATE WMCOMPLEX_SHARED_BUILD)
endif()

target_include_directories(wmcomplex PRIVATE "include")

set_target_properties(wmcomplex
  PROPERTIES
    OUTPUT_NAME 
    "wmcomplex-${PROJECT_VERSION_MAJOR}_${PROJECT_VERSION_MINOR}_${PROJECT_VERSION_PATCH}"
    PREFIX ""
    IMPORT_PREFIX "lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)

################################################################################
# Build the docs
if (${WITH_DOCS})
  find_package(Doxygen REQUIRED)

  set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/docs/wmcomplex")
  set(DOXYGEN_PROJECT_BRIEF "A lightweight complex value library with SIMD optimization")
  set(DOXYGEN_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

  doxygen_add_docs(
    wmcomplex_docs
    "include/"
    ALL
    COMMENT "Building Docs"
  )
endif()

################################################################################
# Build tests
if (${WITH_TESTS})
  include(CTest)
  enable_testing()
  add_subdirectory(src/tests wmcomplex_tests)

  if (NOT ${STATIC_LIB})
    add_custom_command(
      TARGET wmcomplex POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:wmcomplex> 
      "${CMAKE_CURRENT_BINARY_DIR}/wmcomplex_tests/$<TARGET_FILE_NAME:wmcomplex>"
    )
  endif()
endif()