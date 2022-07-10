#==============================================================================
#     Launch_Samples
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME_BASE Launch)
set(TARGET_NAME Ring_Sample_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::Sample::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

# Launch Sample
project(${TARGET_NAME} LANGUAGES C CXX)

if (ANDROID)
    # android needs shared library
    add_library(
        ${TARGET_NAME}
        
        SHARED
        $<TARGET_OBJECTS:Ring::Launch>
    )

    # alias
    add_library(
        ${TARGET_ALIAS_NAME}
        
        ALIAS
        ${TARGET_NAME}
    )
else()
    # executable
    add_executable(
        ${TARGET_NAME}
        $<TARGET_OBJECTS:Ring::Launch>
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
    "Sample_Launch.cpp"
)

if (ANDROID)
    # library dependencies (android needs public?)
    target_link_libraries(
        ${TARGET_NAME}

        PUBLIC
        Ring::Launch
    )
else()
    # library dependencies
    target_link_libraries(
        ${TARGET_NAME}

        PRIVATE
        Ring::Launch
    )
endif()

# properties
set_target_properties(
    ${TARGET_NAME}

    PROPERTIES
    
    FOLDER
    "Samples"
)

# compile options
target_compile_options(
    ${TARGET_NAME}

    PUBLIC
    "$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>"
)
