cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME Ring_Runtime_Test)

project(${TARGET_NAME} LANGUAGES C CXX)

ring_discover_tests(
    TARGET
    ${TARGET_NAME}
    
    SOURCES
    "Test_Runtime.cpp"
    
    LIBRARIES
    Ring::Runtime
)
