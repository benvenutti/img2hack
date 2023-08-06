add_executable(model_tests ScreenMap.test.cpp)

target_link_libraries(model_tests PRIVATE model Catch2::Catch2WithMain)

target_compile_definitions(model_tests PRIVATE TESTS_FILES_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
