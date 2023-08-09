add_library(core STATIC
  src/ScreenMap.cpp
  src/Writer.cpp
  include/core/Hack.hpp
  include/core/ScreenMap.hpp
  include/core/Writer.hpp
)

target_compile_features(core PUBLIC cxx_std_17)

target_include_directories(core PUBLIC include)

target_link_libraries(core PRIVATE Qt6::Core Qt6::Gui)

add_subdirectory(tests)
