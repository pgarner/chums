#!/bin/sh
#
# Copyright 2014 by Philip N. Garner
#
# See the file COPYING for the licence associated with this software.
#
# Author(s):
#   Phil Garner, September 2014
#
rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake

export CC=clang
export CXX=clang++

export CPATH=~/local/include

if [ ! -e FindLibUBE.cmake ]
then
    wget https://github.com/pgarner/libube/raw/master/cmake/FindLibUBE.cmake
fi

# This is the jCard spec
if [ ! -e rfc7095.txt ]
then
    wget http://tools.ietf.org/rfc/rfc7095.txt
fi

cmake \
    -D CMAKE_BUILD_TYPE=debug \
    -D CMAKE_INSTALL_PREFIX=~/local \
    .
