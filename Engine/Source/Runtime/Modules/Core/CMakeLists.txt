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
    "Private/Core.cpp"
)

target_include_directories(
    ${TARGET_NAME}

    PRIVATE
    "Private"

    PUBLIC
    "Public"
)

target_compile_definitions(
    ${TARGET_NAME}

    PUBLIC
    "$<$<PLATFORM_ID:Android>:RING_PLATFORM_ANDROID=1>"
    "$<$<PLATFORM_ID:Windows>:RING_PLATFORM_WINDOWS=1>"
    "$<$<PLATFORM_ID:Linux>:RING_PLATFORM_LINUX=1>"
)

# TODO: ANDROID
target_link_libraries(
    ${TARGET_NAME}

    PUBLIC
    Ring::Modules
    Ring::Window
)

if(${RING_BUILD_TEST})

    add_subdirectory(Tests)

endif()

add_subdirectory(Window)
