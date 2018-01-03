#!/bin/bash -x

qmake -qt=qt5 --version
cmake --version
uname -a
$COMPILER_CXX --version
$COMPILER_CC --version
