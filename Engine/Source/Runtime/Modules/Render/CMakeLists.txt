#==============================================================================
#     Render
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

set(TARGET_NAME_BASE Render)
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
    ${CMAKE_CURRENT_SOURCE_DIR}/Private/Render.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Private/GL/GLRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Private/Vulkan/VulkanRenderer.cpp

    $<$<PLATFORM_ID:Windows>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/GL/WGL/WGLContext.cpp
    >
    $<$<PLATFORM_ID:Linux>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/GL/X11/X11Context.cpp
    >
    $<$<PLATFORM_ID:Android>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/GL/EGL/EGLContext.cpp
    >
)

target_include_directories(
    ${TARGET_NAME}

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Private

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${RingVulkanHppIncludeDirectories}
)

message(
    "target_include_directories=
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
        ${RingVulkanHppIncludeDirectories}"
)

target_compile_definitions(
    ${TARGET_NAME}

    PUBLIC
    $<$<PLATFORM_ID:Android>:
        RING_PLATFORM_ANDROID=1
    >

    $<$<PLATFORM_ID:Windows>:
        RING_PLATFORM_WINDOWS=1
    >

    $<$<PLATFORM_ID:Linux>:
        RING_PLATFORM_LINUX=1
    >
)

target_link_libraries(
    ${TARGET_NAME}
    
    PUBLIC
    Ring::Core

    $<$<PLATFORM_ID:Windows,Linux>:
        glew
    >

    $<$<PLATFORM_ID:Windows>:
        opengl32.lib
    >

    $<$<PLATFORM_ID:Linux>:
        GL
        ${CMAKE_DL_LIBS}
    >

    $<$<PLATFORM_ID:Android>:
        EGL
        GLESv1_CM
    >
)

if(VULKAN_HPP_RUN_GENERATOR)

    add_dependencies(
        ${TARGET_NAME}
        build_vulkan_hpp
    )

endif()

if(${RING_BUILD_TEST})
    add_subdirectory(Tests)
endif()

add_subdirectory(Samples)
