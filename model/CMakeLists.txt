project(model LANGUAGES CXX)

## files:

set(source_files
  src/ScreenMap.cpp
  src/Writer.cpp)

set(header_files
  include/model/Hack.hpp
  include/model/ScreenMap.hpp
  include/model/Writer.hpp)

## library:

add_library(${PROJECT_NAME}
  ${source_files}
  ${header_files})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    include/model)

target_include_directories(${PROJECT_NAME}
  SYSTEM PRIVATE
    ${ImageMagick_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    ${ImageMagick_LIBRARIES})

add_subdirectory(tests)

## install:

install(TARGETS ${PROJECT_NAME}
  EXPORT "${PROJECT_NAME}Config"
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT "${PROJECT_NAME}Config" DESTINATION share/${PROJECT_NAME}/cmake)
export(TARGETS ${PROJECT_NAME} FILE "${PROJECT_NAME}Config.cmake")
