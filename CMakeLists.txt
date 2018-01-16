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

## model:

add_subdirectory(model)

## files:

set(source_files
  view/aboutdialog.cpp
  view/mainwindow.cpp
  main.cpp)

set(header_files
  view/aboutdialog.h
  view/mainwindow.h)

set(ui_files
  view/aboutdialog.ui
  view/mainwindow.ui)

set(qrc_files
  images.qrc)

qt5_wrap_cpp(header_files_moc ${header_files})
qt5_wrap_ui(ui_files_moc ${ui_files})
qt5_add_resources(resources_files ${qrc_files})

## executable:

add_executable(${PROJECT_NAME}
  ${source_files}
  ${header_files}
  ${header_files_moc}
  ${ui_files_moc}
  ${resources_files})

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${ImageMagick_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    model
    ${ImageMagick_LIBRARIES}
    Qt5::Widgets)
