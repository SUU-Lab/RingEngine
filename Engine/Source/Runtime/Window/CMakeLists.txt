cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE Window)

set(TARGET_NAME Ring_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(${TARGET_NAME})
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

find_package(X11)

target_sources(
    ${TARGET_NAME}
    PRIVATE
    "Private/ClientExtent.cpp"
    "Private/WindowExtent.cpp"
    "Private/X11/X11Window.cpp"
    $<$<PLATFORM_ID:Windows>:
            "Private/Windows/WindowsWindow.cpp"

        $<PLATFORM_ID:Linux>:
            "Private/X11/X11Window.cpp"
    >
)

target_include_directories(
    ${TARGET_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/Private"
)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    "${PROJECT_SOURCE_DIR}/Public"
)

if(MSVC)
    target_compile_options(
        ${TARGET_NAME}
        PUBLIC
        "/Zc:__cplusplus"
    )
endif()

if (X11_FOUND)
    target_link_libraries(${TARGET_NAME} PRIVATE X11::X11)
endif()

add_subdirectory(Samples)
add_subdirectory(Tests)
