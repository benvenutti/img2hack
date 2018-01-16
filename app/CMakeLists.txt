project(app VERSION 0.1.0 LANGUAGES CXX)

set(source_files
  src/AboutDialog.cpp
  src/MainWindow.cpp
  src/main.cpp)

set(header_files
  src/AboutDialog.hpp
  src/MainWindow.hpp)

set(ui_files
  src/AboutDialog.ui
  src/MainWindow.ui)

set(qrc_files
  src/images.qrc)

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
