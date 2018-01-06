#!/bin/bash -x

mkdir build
cd build

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
  cmake -DCMAKE_C_COMPILER=$COMPILER_CC -DCMAKE_CXX_COMPILER=$COMPILER_CXX ..
elif [ "$TRAVIS_OS_NAME" == "osx" ]; then
  # On OSX CMake's find_package for ImageMagick is not setting ImageMagick_Magick++_LIBRARY 
  # for the Magick++ component. Here is an evil hack to solve this...

  magickFolder=`brew --prefix imagemagick`/lib/
  magickLib=`ls $magickFolder | grep "++.*HDRI.dylib"`
  magickDir=$magickFolder$magickLib

  cmake -DCMAKE_C_COMPILER=$COMPILER_CC -DCMAKE_CXX_COMPILER=$COMPILER_CXX -DImageMagick_Magick++_LIBRARY=$magickDir -DCMAKE_PREFIX_PATH="`brew --prefix qt`" ..
fi

cmake --build .
