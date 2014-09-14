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

if [[ ! -e FindLibVar.cmake ]]
then
    wget https://github.com/pgarner/libvar/raw/master/cmake/FindLibVar.cmake
fi

cmake \
    -D CMAKE_BUILD_TYPE=debug \
    -D CMAKE_INSTALL_PREFIX=~/local \
    .
