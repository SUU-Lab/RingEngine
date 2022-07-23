#==============================================================================
#     Render_Tests
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME_BASE Render)
set(TARGET_NAME Ring_Test_${TARGET_NAME_BASE})

project(${TARGET_NAME} LANGUAGES C CXX)

ring_discover_tests(
    TARGET
    ${TARGET_NAME}

    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Test_Render.cpp

    LIBRARIES
    Ring::${TARGET_NAME_BASE}
)
