#==============================================================================
#     Render
#==============================================================================

cmake_minimum_required(VERSION 3.18.1)

# ç°ÇæÇØ
if(ANDROID)
    RETURN()
endif()

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

# OpenGL
find_package(OpenGL)


target_sources(
    ${TARGET_NAME}

    PRIVATE
    "Private/Render.cpp"
    "$<$<AND:$<BOOL:${OPENGL_FOUND}>,$<PLATFORM_ID:Windows>>:Private/GL/WGL/WGLContext.cpp>"
    "$<$<AND:$<BOOL:${OPENGL_FOUND}>,$<PLATFORM_ID:Linux>>:Private/GL/X11/X11Context.cpp>"
    "$<$<BOOL:${OPENGL_FOUND}>:Private/GL/GLRenderer.cpp>"
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

target_link_libraries(
    ${TARGET_NAME}
    
    PUBLIC
    Ring::Core
    "$<$<BOOL:${OPENGL_FOUND}>:OpenGL::GL>"
)

if(${RING_BUILD_TEST})
    add_subdirectory(Tests)
endif()

add_subdirectory(Samples)
