add_library(core STATIC
  src/BitmapToAssembly.cpp
  src/ImageToBitmap.cpp
  include/core/Bitmap.h
  include/core/BitmapToAssembly.h
  include/core/Hack.h
  include/core/ImageToBitmap.h
)

target_compile_features(core PUBLIC cxx_std_17)

target_include_directories(core PUBLIC include)

target_link_libraries(core PRIVATE Qt6::Core Qt6::Gui)

add_subdirectory(tests)
