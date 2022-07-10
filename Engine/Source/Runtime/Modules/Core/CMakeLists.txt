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

# Core
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
    "Private/Core.cpp"
)

# include directories
target_include_directories(
    ${TARGET_NAME}

    PRIVATE
    "Private"

    PUBLIC
    "Public"
)

# preprocessor macros
target_compile_definitions(
    ${TARGET_NAME}

    PUBLIC
    "$<$<PLATFORM_ID:Android>:RING_PLATFORM_ANDROID=1>"
    "$<$<PLATFORM_ID:Windows>:RING_PLATFORM_WINDOWS=1>"
    "$<$<PLATFORM_ID:Linux>:RING_PLATFORM_LINUX=1>"
)

if(NOT ANDROID)
    target_link_libraries(
        ${TARGET_NAME}

        PRIVATE
        Ring::Window
    )
endif()

if(${RING_BUILD_TEST})
    add_subdirectory(Tests)
endif()

if(NOT ANDROID)
    add_subdirectory(Window)
endif()

