qt_standard_project_setup()

qt_add_executable(img2hack-gui-qtwidget
  src/AboutDialog.cpp
  src/AboutDialog.hpp
  src/AboutDialog.ui
  src/MainWindow.cpp
  src/MainWindow.hpp
  src/MainWindow.ui
  src/images.qrc
  src/main.cpp
)

target_link_libraries(img2hack-gui-qtwidget
  PUBLIC Qt6::Widgets
  PRIVATE core
)

# Prevent the creation of a console window on Windows
set_target_properties(img2hack-gui-qtwidget PROPERTIES
  WIN32_EXECUTABLE ON
)
