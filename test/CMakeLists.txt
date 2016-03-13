#
# Copyright 2016 by Philip N. Garner
#
# See the file COPYING for the licence associated with this software.
#
# Author(s):
#   Phil Garner, March 2016
#

# Testing
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
add_definitions(-DTEST_DIR="${TEST_DIR}")

add_executable(test-card test-card.cpp)
target_link_libraries(test-card card-shared)
add_test(
  NAME card
  COMMAND ${CMAKE_COMMAND} -D TEST_DIR=${TEST_DIR} -P ${CMAKE_CURRENT_SOURCE_DIR}/test-card.cmake
  )
