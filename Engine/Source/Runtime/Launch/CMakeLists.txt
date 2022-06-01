cmake_minimum_required(VERSION 3.20)

if(ANDROID)
    # Windows で発生する Invalid escape sequence を回避する
    string(REPLACE "\\" "/" NDK_DIR ${ANDROID_NDK})

    add_library(
        native_app_glue
        STATIC
        "${NDK_DIR}/sources/android/native_app_glue/android_native_app_glue.c"
    )

    # project() コマンドよりも手前で呼び出さないとリンクに失敗する。
    set(CMAKE_SHARED_LINKER_FLAGS
            "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate"
    )
endif() # ANDROID

set(TARGET_NAME_BASE Launch)

set(TARGET_NAME Ring_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

if(ANDROID)
    add_library(${TARGET_NAME}
        OBJECT
        "$<$<PLATFORM_ID:Android>:${CMAKE_CURRENT_SOURCE_DIR}/Private/Android/AndroidMain.cpp>"
        "$<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/Private/Windows/WindowsMain.cpp>"
        "$<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/Private/Linux/LinuxMain.cpp>"
    )

    # shared libraries need PIC
    set_property(TARGET
        ${TARGET_NAME}
        PROPERTY POSITION_INDEPENDENT_CODE 1
    )
else()
    add_library(${TARGET_NAME}
        "$<$<PLATFORM_ID:Android>:${CMAKE_CURRENT_SOURCE_DIR}/Private/Android/AndroidMain.cpp>"
        "$<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/Private/Windows/WindowsMain.cpp>"
        "$<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/Private/Linux/LinuxMain.cpp>"
    )
endif()
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})


target_include_directories(
    ${TARGET_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/Private"
    "$<$<PLATFORM_ID:Android>:${NDK_DIR}/sources/android/native_app_glue>"
    PUBLIC
    "${PROJECT_SOURCE_DIR}/Public"
)

target_compile_definitions(
    ${TARGET_NAME}
    PUBLIC
    "$<$<PLATFORM_ID:Android>:RING_PLATFORM_ANDROID=1>"
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

if(ANDROID)
    find_library(android-lib android)

    find_library(log-lib log)

    target_link_libraries(
        ${TARGET_NAME}
        PUBLIC
        native_app_glue
        ${log-lib}
        ${android-lib}
    )
endif() # ANDROID

#if(${RING_BUILD_TEST})
#    add_subdirectory(Tests)
#endif()

add_subdirectory(Samples)
