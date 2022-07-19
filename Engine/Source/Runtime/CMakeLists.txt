#==============================================================================
#     Runtime
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME_BASE Runtime)
set(TARGET_NAME Ring_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::${TARGET_NAME_BASE})
set(LAUNCH_TARGET_NAME Launch)

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

ring_add_executable(
    TARGET
    ${TARGET_NAME}

    SOURCES
    PRIVATE
    "Private/Runtime.cpp"

    INCLUDE_DIRECTORIES
    PRIVATE
    "Private"

    PUBLIC
    "Public"

    COMPILE_OPTIONS
    PUBLIC
    "$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>"

    LIBRARIES
    $<$<PLATFORM_ID:Windows,Linux>:Ring::Core>
    $<$<PLATFORM_ID:Windows,Linux>:Ring::Render>
)

add_subdirectory(Launch)
add_subdirectory(Modules)
