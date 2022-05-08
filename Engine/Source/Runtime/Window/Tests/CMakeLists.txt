cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME Ring_Window_Test)

project(${TARGET_NAME} LANGUAGES C CXX)

add_executable(${TARGET_NAME}
    "${PROJECT_SOURCE_DIR}/Test_ClientExtent.cpp"
    "${PROJECT_SOURCE_DIR}/Test_WindowExtent.cpp"
)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Tests")
target_link_libraries(${TARGET_NAME} PRIVATE Ring::Window gtest_main gtest)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
