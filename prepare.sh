#!/bin/sh
#
# Copyright 2016 by Philip N. Garner
#
# See the file COPYING for the licence associated with this software.
#
# Author(s):
#   Phil Garner, March 2016
#

if [ ! -e FindLibUBE.cmake ]
then
    curl -LO https://github.com/pgarner/libube/raw/master/cmake/FindLibUBE.cmake
fi

# This is the jCard spec
if [ ! -e rfc7095.txt ]
then
    curl -LO http://tools.ietf.org/rfc/rfc7095.txt
fi

