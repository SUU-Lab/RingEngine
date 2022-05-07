cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE Runtime)

set(TARGET_NAME Ring_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_executable(${TARGET_NAME} Main.cpp)
