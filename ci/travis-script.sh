#!/bin/bash -x

mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=$COMPILER ..
cmake --build .
