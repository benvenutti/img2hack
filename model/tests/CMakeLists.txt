add_executable(model_tests ScreenMap.test.cpp)

target_link_libraries(model_tests PRIVATE Catch2::Catch2WithMain)
