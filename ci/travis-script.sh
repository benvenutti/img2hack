#!/bin/bash -x

mkdir build
cd build

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
  cmake -DCMAKE_C_COMPILER=$COMPILER_CC -DCMAKE_CXX_COMPILER=$COMPILER_CXX ..
elif [ "$TRAVIS_OS_NAME" == "osx" ]; then
  cmake -DCMAKE_C_COMPILER=$COMPILER_CC -DCMAKE_CXX_COMPILER=$COMPILER_CXX -DImageMagick_Magick++_LIBRARY="$( pkg-config --libs Magick++ )" -DCMAKE_PREFIX_PATH="`brew --prefix qt`" ..
fi

cmake --build .
