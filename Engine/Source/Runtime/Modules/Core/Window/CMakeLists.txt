#==============================================================================
#     Window
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

if(ANDROID)
    RETURN()
endif()

set(TARGET_NAME_BASE Window)
set(TARGET_NAME Ring_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

# Window
project(${TARGET_NAME} LANGUAGES C CXX)

# library
add_library(
    ${TARGET_NAME}

    STATIC
)

# alias
add_library(
    ${TARGET_ALIAS_NAME}

    ALIAS
    ${TARGET_NAME}
)

# sources
target_sources(
    ${TARGET_NAME}

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Private/ClientExtent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Private/WindowExtent.cpp

    $<$<PLATFORM_ID:Windows>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/Windows/WindowsWindow.cpp
    >

    $<$<PLATFORM_ID:Linux>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/X11/X11Window.cpp
    >
)

# include directories
target_include_directories(
    ${TARGET_NAME}

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Private

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

# preprocessor macros
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

find_package(X11)
if (X11_FOUND)
    # library dependencies
    target_link_libraries(
        ${TARGET_NAME}

        PRIVATE
        X11::X11
    )
endif()

if(${RING_BUILD_TEST})
    add_subdirectory(Tests)
endif()

add_subdirectory(Samples)
