#
# Copyright 2014 by Philip N. Garner
#
# See the file COPYING for the licence associated with this software.
#
# Author(s):
#   Phil Garner, September 2014
#

cmake_minimum_required(VERSION 2.8)

project(chums)
set(VERSION 0.1)

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(LibUBE REQUIRED)
include_directories(${LIBUBE_INCLUDE_DIRS})
set(TARGET_LIBS ${LIBUBE_LIBRARIES})

# Modules & library
add_subdirectory(lube)

# Main executable
add_executable(chums chums.cpp)
target_link_libraries(chums card-shared)

# Family tree thing
add_executable(tree tree.cpp familytree.cpp)
target_link_libraries(tree ${TARGET_LIBS})

# Tests
enable_testing()
add_subdirectory(test)
