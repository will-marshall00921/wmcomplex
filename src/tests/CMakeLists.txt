# wmcomplex -- wmcomplex_tests -- CMakeLists.txt
# Author: Will Marshall
# Created: 4/15/2026, 7:58:03 PM

################################################################################
# Test Addition

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(wmcomplex_test_add
  wmcomplex_test_add.cpp
)
target_link_libraries(wmcomplex_test_add
  PRIVATE
    wmcomplex
)
add_test(
  NAME wmcomplex_test_add
  COMMAND $<TARGET_FILE:wmcomplex_test_add>
)

################################################################################
# Test Subtraction

add_executable(wmcomplex_test_sub
  wmcomplex_test_sub.cpp
)
target_link_libraries(wmcomplex_test_sub
  PRIVATE
    wmcomplex
)
add_test(
  NAME wmcomplex_test_sub
  COMMAND $<TARGET_FILE:wmcomplex_test_sub>
)

################################################################################
# Test Multiplication

add_executable(wmcomplex_test_mul
  wmcomplex_test_mul.cpp
)
target_link_libraries(wmcomplex_test_mul
  PRIVATE
    wmcomplex
)
add_test(
  NAME wmcomplex_test_mul
  COMMAND $<TARGET_FILE:wmcomplex_test_mul>
)

################################################################################
# Test Division

add_executable(wmcomplex_test_div
  wmcomplex_test_div.cpp
)
target_link_libraries(wmcomplex_test_div
  PRIVATE
    wmcomplex
)
add_test(
  NAME wmcomplex_test_div
  COMMAND $<TARGET_FILE:wmcomplex_test_div>
)