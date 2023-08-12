qt_standard_project_setup()

set(RESOURCES "")

qt_add_resources(RESOURCES src/images.qrc)

qt_add_executable(img2hack-gui-qtwidget
  src/AboutDialog.cpp
  src/AboutDialog.h
  src/AboutDialog.ui
  src/MainWindow.cpp
  src/MainWindow.h
  src/MainWindow.ui
  src/main.cpp
  ${RESOURCES}
)

target_link_libraries(img2hack-gui-qtwidget
  PUBLIC Qt6::Widgets
  PRIVATE core
)

# Prevent the creation of a console window on Windows
set_target_properties(img2hack-gui-qtwidget PROPERTIES
  WIN32_EXECUTABLE ON
)
