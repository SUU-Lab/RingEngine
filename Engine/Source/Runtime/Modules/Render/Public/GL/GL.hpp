#pragma once

#if RING_PLATFORM_WINDOWS
#include "glew.hpp"
#endif

#if RING_PLATFORM_LINUX
#include "glew.hpp"
#include "glfw.hpp"
#endif

#if RING_PLATFORM_ANDROID
#include <EGL/egl.h>
#include <GLES/gl.h>
#endif
