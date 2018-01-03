cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(img2hack VERSION 0.1.0 LANGUAGES CXX)

## build settings:

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type" FORCE)
endif()

set(CMAKE_CXX_FLAGS_RELEASE -O2)

## 3rd party dependencies:

find_package(ImageMagick COMPONENTS Magick++ REQUIRED)
find_package(Qt5Widgets REQUIRED)

## files:

set(source_files
  model/screenmap.cpp
  model/writer.cpp
  view/aboutdialog.cpp
  view/mainwindow.cpp
  main.cpp)

set(header_files
  model/hack.h
  model/screenmap.h
  model/writer.h
  view/aboutdialog.h
  view/mainwindow.h)

set(ui_files
  view/aboutdialog.ui
  view/mainwindow.ui)

qt5_wrap_cpp(header_files_moc ${header_files})
qt5_wrap_ui(ui_files_moc ${ui_files})

## executable:

add_executable(${PROJECT_NAME}
  ${source_files}
  ${header_files}
  ${header_files_moc}
  ${ui_files_moc})

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${ImageMagick_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR})

target_link_libraries (${PROJECT_NAME}
  PUBLIC
    ${ImageMagick_LIBRARIES}
    Qt5::Widgets)
