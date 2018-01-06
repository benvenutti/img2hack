#!/bin/bash -x

mkdir build
cd build

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
  cmake -DCMAKE_C_COMPILER=$COMPILER_CC -DCMAKE_CXX_COMPILER=$COMPILER_CXX ..
elif [ "$TRAVIS_OS_NAME" == "osx" ]; then
  # CMake's find_package for ImageMagick is not setting ImageMagick_Magick++_LIBRARY 
  # for the Magick++ component. Here is an evil hack to solve this...

  magick++_folder=`brew --prefix imagemagick`/lib/
  magick++_lib=`ls $magick++_folder | grep ++ | grep HDRI.dylib`
  magick++_path=$magick++_folder$magick++_lib

  cmake -DCMAKE_C_COMPILER=$COMPILER_CC -DCMAKE_CXX_COMPILER=$COMPILER_CXX -DImageMagick_Magick++_LIBRARY=$magick++_path -DCMAKE_PREFIX_PATH="`brew --prefix qt`" ..
fi

cmake --build .
