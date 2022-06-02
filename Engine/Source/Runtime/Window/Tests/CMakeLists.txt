cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME Ring_Window_Test)

project(${TARGET_NAME} LANGUAGES C CXX)

add_executable(
    ${TARGET_NAME}
    "Test_ClientExtent.cpp"
    "Test_WindowExtent.cpp"
    "Test_Window.cpp"
)

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    Ring::Window GTest::gtest GTest::gtest_main
)

ring_discover_tests(${TARGET_NAME})
