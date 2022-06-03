cmake_minimum_required(VERSION 3.18.1)

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
    "Private/ClientExtent.cpp"
    "Private/WindowExtent.cpp"
    "$<$<PLATFORM_ID:Windows>:Private/Windows/WindowsWindow.cpp>"
    "$<$<PLATFORM_ID:Linux>:Private/X11/X11Window.cpp>"
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
