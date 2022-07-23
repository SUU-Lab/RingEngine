#==============================================================================
#     Core
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME_BASE Core)
set(TARGET_NAME Ring_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(
    ${TARGET_NAME}

    STATIC
)

add_library(
    ${TARGET_ALIAS_NAME}

    ALIAS
    ${TARGET_NAME}
)

target_sources(
    ${TARGET_NAME}

    PRIVATE
    $<$<PLATFORM_ID:Windows,Linux>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/Core.cpp
    >
    $<$<PLATFORM_ID:Android>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/Android/AndroidCore.cpp
    >
)

target_include_directories(
    ${TARGET_NAME}

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Private

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Launch/Public
)

target_compile_definitions(
    ${TARGET_NAME}

    PUBLIC
    $<$<PLATFORM_ID:Android>:
        RING_PLATFORM_ANDROID=1
    >

    $<$<PLATFORM_ID:Windows>:
        RING_PLATFORM_WINDOWS=1
    >

    $<$<PLATFORM_ID:Linux>:
        RING_PLATFORM_LINUX=1
    >
)

target_link_libraries(
    ${TARGET_NAME}

    PUBLIC
    Ring::Modules

    $<$<PLATFORM_ID:Windows,Linux>:Ring::Window>
)

if(${RING_BUILD_TEST})

    add_subdirectory(Tests)

endif()

if(NOT ANDROID)

    add_subdirectory(Window)

endif()
