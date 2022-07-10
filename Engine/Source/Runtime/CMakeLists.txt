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

# Runtime
project(${TARGET_NAME} LANGUAGES C CXX)


if (ANDROID)
    # android needs shared library
    add_library(
        ${TARGET_NAME}
        
        SHARED
        $<TARGET_OBJECTS:Ring::${LAUNCH_TARGET_NAME}>
    )

    # alias
    add_library(
        ${TARGET_ALIAS_NAME}
        
        ALIAS
        ${TARGET_NAME}
    )

    # export "ANativeActivity_onCreate"
    set_target_properties(
        ${TARGET_NAME}

        PROPERTIES
        APPEND_STRING
        PROPERTY
        LINK_FLAGS " -u ANativeActivity_onCreate"
    )
else()
    # executable
    add_executable(
        ${TARGET_NAME}
        $<TARGET_OBJECTS:Ring::${LAUNCH_TARGET_NAME}>
    )

    # alias
    add_executable(
        ${TARGET_ALIAS_NAME}
        
        ALIAS
        ${TARGET_NAME}
    )
endif()

# sources
target_sources(
    ${TARGET_NAME}

    PRIVATE
    "Private/Runtime.cpp"
)

# include directories
target_include_directories(
    ${TARGET_NAME}

    PRIVATE
    "Private"

    PUBLIC
    "Public"
)

if (ANDROID)
    # library dependencies (android needs public?)
    target_link_libraries(
        ${TARGET_NAME}

        PUBLIC
        Ring::${LAUNCH_TARGET_NAME}
    )
else()
    # library dependencies
    target_link_libraries(
        ${TARGET_NAME}

        PRIVATE
        Ring::${LAUNCH_TARGET_NAME}
    )
endif()

# preprocessor macros
target_compile_definitions(
    ${TARGET_NAME}

    PUBLIC
    "$<$<PLATFORM_ID:Android>:RING_PLATFORM_ANDROID=1>"
    "$<$<PLATFORM_ID:Windows>:RING_PLATFORM_WINDOWS=1>"
    "$<$<PLATFORM_ID:Linux>:RING_PLATFORM_LINUX=1>"
)

# compile options
target_compile_options(
    ${TARGET_NAME}

    PUBLIC
    "$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>"
)

add_subdirectory(Launch)
add_subdirectory(Modules)
