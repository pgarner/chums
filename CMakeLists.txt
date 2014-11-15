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

# Card library
add_library(card SHARED card.cpp)
set_target_properties(card
  PROPERTIES OUTPUT_NAME "card"
  PUBLIC_HEADER "card.h"
  INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/libvar"
  )
target_link_libraries(card ${TARGET_LIBS})

# Main executable
add_executable(chums chums.cpp)
target_link_libraries(chums ${TARGET_LIBS})

# The Windows Address Book module
add_library(wab-lib MODULE wabfile.cpp)
set_target_properties(wab-lib
  PROPERTIES OUTPUT_NAME "wab"
  )
target_link_libraries(wab-lib card)
list(APPEND MODULE_TARGETS wab-lib)

# The vCard module
add_library(vcf-lib MODULE vcffile.cpp)
set_target_properties(vcf-lib
  PROPERTIES OUTPUT_NAME "vcf"
  )
target_link_libraries(vcf-lib card)
list(APPEND MODULE_TARGETS vcf-lib)

# The LDIF module
add_library(ldif-lib MODULE ldiffile.cpp)
set_target_properties(ldif-lib
  PROPERTIES OUTPUT_NAME "ldif"
  )
list(APPEND MODULE_TARGETS ldif-lib)
