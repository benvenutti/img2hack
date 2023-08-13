qt_standard_project_setup()

qt_add_executable(img2hack-gui-qtquick
  main.cpp
)

target_link_libraries(img2hack-gui-qtquick PUBLIC
  Qt6::Core
  Qt6::Gui
  Qt6::Qml
  Qt6::Quick
)

qt_add_qml_module(img2hack-gui-qtquick
  URI     example
  VERSION 1.0
  QML_FILES
    main.qml
  SOURCES
    DrawingCanvas.cpp
    DrawingCanvas.h
)
