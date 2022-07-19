#==============================================================================
#     glew
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

if(ANDROID)
    RETURN()
endif()

set(TARGET_NAME glew)

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C)

# NOTE: Remove /RTC1 option from default compiler options for Visual Studio
# https://github.com/mogemimi/pomdog/blob/main/cmake/dependencies/glew/CMakeLists.txt
# https://elda27.hatenablog.com/entry/2016/09/28/000947
STRING(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")


add_library(
    ${TARGET_NAME}

    STATIC
)

target_sources(
    ${TARGET_NAME}

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glew.c
)

target_include_directories(
    ${TARGET_NAME}

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(
    ${TARGET_NAME}

    PRIVATE
    GLEW_STATIC
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    $<$<PLATFORM_ID:Windows>:
        WIN32
        _LIB
        WIN32_LEAN_AND_MEAN
    >
)

target_compile_options(
    ${TARGET_NAME}

    PRIVATE
    $<$<CXX_COMPILER_ID:Clang,AppleClang,GNU>:
        $<$<CONFIG:Debug>:-g;-O0>
        $<$<CONFIG:Release>:-O3>
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /nologo
        /W3
        /O2
        /Ob1
        /GF
        /Gy
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    >
)

