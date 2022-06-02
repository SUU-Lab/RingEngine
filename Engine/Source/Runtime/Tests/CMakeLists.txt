cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME Ring_Runtime_Test)

project(${TARGET_NAME} LANGUAGES C CXX)

add_executable(
    ${TARGET_NAME}
    "Test_Runtime.cpp"
)

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    Ring::Runtime GTest::gtest GTest::gtest_main
)

ring_discover_tests(${TARGET_NAME})
