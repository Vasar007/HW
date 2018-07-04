#!/bin/bash

set -x

EXTRA_CMAKE_FLAGS=-DCMAKE_PREFIX_PATH='/usr/include/x86_64-linux-gnu/qt5'
BUILD_TYPE==-DCMAKE_BUILD_TYPE=Debug

CC=gcc
CXX=g++

mkdir build
cd build

cmake -G Ninja -DCMAKE_BUILD_TYPE=$BUILD_TYPE $EXTRA_CMAKE_FLAGS -DBUILD_TESTING=ON .. || exit 1
cmake --build . -- -v || exit 1
ASAN_OPTIONS=alloc_dealloc_mismatch=0 ctest . || exit 1
