cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# project:

project(img2hack
  VERSION 0.1.0
  DESCRIPTION "Convert images into hack (Nand2Tetris) assembly code"
  LANGUAGES CXX
)

# dependencies:

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1
)

FetchContent_MakeAvailable(Catch2)

find_package(Qt6 6.2 COMPONENTS Core Gui Widgets REQUIRED)

# compiler definitions:

if(MSVC)
  add_compile_options(/W4 /w14545 /w34242 /w34254 /w34287 /w44263 /w44265
    /w44296 /w44311 /w44826 /we4289 /w14546 /w14547 /w14549 /w14555 /w14619
    /w14905 /w14906 /w14928)
else()
  add_compile_options(-Wall -Wextra -Wconversion -Wsign-conversion -Wshadow
    -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wcast-qual -Wunused
    -Woverloaded-virtual -pedantic)
endif()

# subdirectories:

enable_testing(true)

add_subdirectory(app)
add_subdirectory(core)
