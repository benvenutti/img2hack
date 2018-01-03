#!/bin/bash -x

mkdir build
cd build
cmake -DCMAKE_C_COMPILER=$COMPILER_CC -DCMAKE_CXX_COMPILER=$COMPILER_CXX ..
cmake --build .
