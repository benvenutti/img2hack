add_executable(core_tests
  BitmapToAssembly.test.cpp
  ImageToBitmap.test.cpp
)

target_compile_features(core_tests PUBLIC cxx_std_17)

target_link_libraries(core_tests PRIVATE core Catch2::Catch2WithMain)

target_compile_definitions(core_tests PRIVATE TESTS_FILES_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_test(NAME CoreTestSuite COMMAND core_tests)
