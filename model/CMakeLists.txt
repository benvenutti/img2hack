## library:

add_library(model STATIC
  src/ScreenMap.cpp
  src/Writer.cpp
  include/model/Hack.hpp
  include/model/ScreenMap.hpp
  include/model/Writer.hpp
)

target_include_directories(model PUBLIC include)

target_link_libraries(model PRIVATE Qt6::Core Qt6::Gui)

add_subdirectory(tests)
