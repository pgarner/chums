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
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

find_package(LibVar REQUIRED)
include_directories(${LIBVAR_INCLUDE_DIR})
set(TARGET_LIBS ${LIBVAR_LIBRARIES})

# Main executable
add_executable(chums chums.cpp)
target_link_libraries(chums ${TARGET_LIBS})

# The Windows Address Book module
add_library(wab-lib MODULE wabfile.cpp)
set_target_properties(wab-lib
  PROPERTIES OUTPUT_NAME "wab"
  )
list(APPEND MODULE_TARGETS wab-lib)

# The vCard module
add_library(vcf-lib MODULE vcffile.cpp)
set_target_properties(vcf-lib
  PROPERTIES OUTPUT_NAME "vcf"
  )
list(APPEND MODULE_TARGETS vcf-lib)
