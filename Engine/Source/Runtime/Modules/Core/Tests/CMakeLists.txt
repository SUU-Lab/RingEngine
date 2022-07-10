#==============================================================================
#     Core_Tests
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME_BASE Core)
set(TARGET_NAME Ring_Test_${TARGET_NAME_BASE})

project(${TARGET_NAME} LANGUAGES C CXX)

ring_discover_tests(
    TARGET
    ${TARGET_NAME}

    SOURCES
    "Test_Core.cpp"

    LIBRARIES
    Ring::Core
)
