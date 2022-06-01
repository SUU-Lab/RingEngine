cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE Runtime)

set(TARGET_NAME Ring_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(${TARGET_NAME}
    ${PROJECT_SOURCE_DIR}/Private/Runtime.cpp
)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Private)
target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Public)

if(MSVC)
    target_compile_options(${TARGET_NAME} PUBLIC "/Zc:__cplusplus")
endif()

if(${RING_BUILD_TEST})
    if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Windows")
        string(REPLACE "/" "\\" RING_CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR})
    else()
        string(REPLACE "\\" "/" RING_CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR})
    endif()
    file(
        WRITE
        ${CMAKE_SOURCE_DIR}/../Build/Android/${ANDROID_ABI}/cmake_binary_dir.txt
        ${CMAKE_SOURCE_DIR}/../Build/Android/${ANDROID_ABI})
    add_subdirectory(Tests)
endif()

add_subdirectory(Launch)

if(NOT ANDROID)
    add_subdirectory(Window)
endif()
