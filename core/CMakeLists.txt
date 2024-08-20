# core library:

add_library(
  core
  STATIC
  include/core/Bitmap.h
  include/core/BitmapToAssembly.h
  include/core/Hack.h
  include/core/ImageToBitmap.h
  src/BitmapToAssembly.cpp
  src/ImageToBitmap.cpp
)

target_compile_features(core PUBLIC cxx_std_17)

target_include_directories(core PUBLIC include)

target_link_libraries(
  core
  PRIVATE
    Qt6::Core
    Qt6::Gui
)

# tests:

add_subdirectory(tests)
