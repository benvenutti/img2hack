cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# project:

project(
  img2hack
  VERSION      0.1.0
  DESCRIPTION  "Convert images into hack (nand2tetris) bitmaps"
  HOMEPAGE_URL https://github.com/benvenutti/img2hack
  LANGUAGES    CXX
)

# modules:

include(CMakeDependentOption)
include(FetchContent)

# project options:

option(BUILD_APP_QTQUICK "Build img2hack (QtQuick-based application)" ON)
option(BUILD_APP_QTWIDGET "Build img2hack (QtWidget-based application)" ON)
option(BUILD_TESTS "Build tests" ON)
cmake_dependent_option(CODE_COVERAGE "Enable code coverage" OFF "BUILD_TESTS" OFF)

# dependencies:

find_package(Qt6 6.2 COMPONENTS Core Gui Quick Widgets Qml REQUIRED)

if(BUILD_TESTS)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.1
  )

  FetchContent_MakeAvailable(Catch2)
endif()

# compiler definitions:

if(MSVC)
  add_compile_options(
    # warnings:
    /W4 /w14545 /w34242 /w34254 /w34287 /w44263 /w44265  /w44296 /w44311 /w44826
    /we4289 /w14546 /w14547 /w14549 /w14555 /w14619 /w14905 /w14906 /w14928

    # optimization levels:
    $<$<CONFIG:DEBUG>:/Od>
  )
else()
  add_compile_options(
    # warnings:
    -Wall -Wconversion -Wsign-conversion -Wshadow -Wnon-virtual-dtor -Wcast-qual
    -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -pedantic -Wextra

    # optimization levels:
    $<$<CONFIG:DEBUG>:-O0>

    # coverage:
    $<$<BOOL:${CODE_COVERAGE}>:-coverage>
  )

  add_link_options(
    # coverage:
    $<$<BOOL:${CODE_COVERAGE}>:-coverage>
  )
endif()

# testing:

if(BUILD_TESTS)
  enable_testing()
endif()

# subdirectories:

if(BUILD_APP_QTQUICK)
  add_subdirectory(app-qtquick)
endif()

if(BUILD_APP_QTWIDGET)
  add_subdirectory(app-qtwidget)
endif()

add_subdirectory(core)
