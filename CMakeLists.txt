cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(img2hack VERSION 0.1.0 LANGUAGES CXX)

## build settings:

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type" FORCE)
endif()

set(CMAKE_CXX_FLAGS_RELEASE -O2)

include(GNUInstallDirs)

## 3rd party dependencies:

find_package(ImageMagick COMPONENTS Magick++ REQUIRED)
find_package(Qt5Widgets REQUIRED)

## projects:

add_subdirectory(app)
add_subdirectory(model)
