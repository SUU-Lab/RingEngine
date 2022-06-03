cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME_BASE Window)
set(TARGET_NAME Ring_Sample_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::Sample::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

# Window Sample
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
    "Sample_Window.cpp"
)

# properties
set_target_properties(
    ${TARGET_NAME}
    
    PROPERTIES
    
    FOLDER
    "Samples"
)

# library dependencies
target_link_libraries(
    ${TARGET_NAME}

    PRIVATE
    Ring::Window
)

# compile options
target_compile_options(
    ${TARGET_NAME}

    PUBLIC
    "$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>"
)
