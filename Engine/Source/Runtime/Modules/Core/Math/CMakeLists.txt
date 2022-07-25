#==============================================================================
#     Math
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME_BASE Math)
set(TARGET_NAME Ring_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(
    ${TARGET_NAME}

    INTERFACE
)

add_library(
    ${TARGET_ALIAS_NAME}

    ALIAS
    ${TARGET_NAME}
)

target_sources(
    ${TARGET_NAME}

    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Public/Math.hpp
)

target_include_directories(
    ${TARGET_NAME}

    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${RingEigenIncludeDirectories}
)
