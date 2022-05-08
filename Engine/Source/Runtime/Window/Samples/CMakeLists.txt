cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE Window)

set(TARGET_NAME Ring_Sample_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::Sample::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_executable(${TARGET_NAME})
add_executable(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

target_sources(
    ${TARGET_NAME}
    PRIVATE
    "Sample_Window.cpp"
)

set_target_properties(
    ${TARGET_NAME}
    PROPERTIES FOLDER
    "Samples"
)

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    Ring::Window
)

if(MSVC)
    target_compile_options(
        ${TARGET_NAME}
        PUBLIC
        "/Zc:__cplusplus"
    )
endif()
