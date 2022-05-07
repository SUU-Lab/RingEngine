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

add_subdirectory(Tests)
