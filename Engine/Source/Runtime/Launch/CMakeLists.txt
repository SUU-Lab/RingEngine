#==============================================================================
#     Launch
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

if(ANDROID)
    # Windows で発生する Invalid escape sequence を回避する
    string(REPLACE "\\" "/" NDK_DIR ${ANDROID_NDK})

    add_library(
        native_app_glue
        STATIC
        "${NDK_DIR}/sources/android/native_app_glue/android_native_app_glue.c"
    )
endif() # ANDROID

set(TARGET_NAME_BASE Launch)
set(TARGET_NAME Ring_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(
    ${TARGET_NAME}

    OBJECT
)

add_library(
    ${TARGET_ALIAS_NAME}

    ALIAS
    ${TARGET_NAME}
)

target_sources(
    ${TARGET_NAME}

    PRIVATE
    "$<$<PLATFORM_ID:Android>:Private/Android/AndroidMain.cpp>"
    "$<$<PLATFORM_ID:Windows>:Private/Windows/WindowsMain.cpp>"
    "$<$<PLATFORM_ID:Linux>:Private/Linux/LinuxMain.cpp>"
)

target_include_directories(
    ${TARGET_NAME}

    PRIVATE
    "Private"
    "$<$<PLATFORM_ID:Android>:${NDK_DIR}/sources/android/native_app_glue>"

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

if(ANDROID)

    find_library(
        android-lib
        android
    )

    find_library(
        log-lib
        log
    )

    target_link_libraries(
        ${TARGET_NAME}

        PUBLIC
        native_app_glue
        ${android-lib}
        ${log-lib}
    )

    set_target_properties(
        ${TARGET_NAME}

        PROPERTIES
        POSITION_INDEPENDENT_CODE 1
    )

endif() # ANDROID

add_subdirectory(Samples)
