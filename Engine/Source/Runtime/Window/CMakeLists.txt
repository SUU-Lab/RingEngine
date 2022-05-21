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

target_sources(
    ${TARGET_NAME}
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/ClientExtent.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/WindowExtent.cpp"
    "$<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/Private/Windows/WindowsWindow.cpp>"
    "$<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/Private/X11/X11Window.cpp>"
)

target_include_directories(
    ${TARGET_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/Private"
    PUBLIC
    "${PROJECT_SOURCE_DIR}/Public"
)

target_compile_definitions(
    ${TARGET_NAME}
    PUBLIC
    "$<$<PLATFORM_ID:Windows>:RING_PLATFORM_WINDOWS=1>"
    "$<$<PLATFORM_ID:Linux>:RING_PLATFORM_LINUX=1>"
)

if(MSVC)
    target_compile_options(
        ${TARGET_NAME}
        PUBLIC
        "/Zc:__cplusplus"
    )
endif()

find_package(X11)
if (X11_FOUND)
    target_link_libraries(${TARGET_NAME} PRIVATE X11::X11)
endif()


if(${RING_BUILD_TEST})
    add_subdirectory(Tests)
endif()

add_subdirectory(Samples)
