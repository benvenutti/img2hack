qt_standard_project_setup()

qt_add_executable(img2hack-gui-qtquick
  src/main.cpp
)

target_link_libraries(img2hack-gui-qtquick PRIVATE Qt6::Gui Qt6::Quick)

qt_add_qml_module(img2hack-gui-qtquick
  URI /
  RESOURCE_PREFIX /
  VERSION 1.0
  QML_FILES resources/qml/main.qml
)
