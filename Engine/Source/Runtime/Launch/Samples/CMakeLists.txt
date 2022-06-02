cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME_BASE Launch)

set(TARGET_NAME Ring_Sample_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::Sample::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

if (ANDROID)
    add_library(${TARGET_NAME} SHARED $<TARGET_OBJECTS:Ring::Launch>)
    add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})
else()
    add_executable(${TARGET_NAME})
    add_executable(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})
endif()

target_sources(
    ${TARGET_NAME}
    PRIVATE
    "Sample_Launch.cpp"
)

set_target_properties(
    ${TARGET_NAME}
    PROPERTIES FOLDER
    "Samples"
)

if (ANDROID)
    target_link_libraries(
        ${TARGET_NAME}
        PUBLIC
        Ring::Launch
    )
else()
    target_link_libraries(
        ${TARGET_NAME}
        PRIVATE
        Ring::Launch
    )
endif()

if(MSVC)
    target_compile_options(
        ${TARGET_NAME}
        PUBLIC
        "/Zc:__cplusplus"
    )
endif()
