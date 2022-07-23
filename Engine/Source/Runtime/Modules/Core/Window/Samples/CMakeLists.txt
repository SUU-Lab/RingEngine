#==============================================================================
#     Window_Samples
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME_BASE Window)
set(TARGET_NAME Ring_Sample_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::Sample::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

ring_add_executable(
    TARGET
    ${TARGET_NAME}

    PROPERTIES
    FOLDER
    "Samples"

    SOURCES
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Sample_Window.cpp

    LIBRARIES
    PRIVATE
    Ring::${TARGET_NAME_BASE}

    COMPILE_OPTIONS
    PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
        /Zc:__cplusplus
    >
)
