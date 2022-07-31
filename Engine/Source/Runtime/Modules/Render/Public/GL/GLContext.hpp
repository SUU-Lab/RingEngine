#pragma once

#if RING_PLATFORM_WINDOWS

#include "WGL/WGLContext.hpp"

#elif RING_PLATFORM_LINUX

#include "GLFW/GLFWContext.hpp"

#elif RING_PLATFORM_ANDROID

#include "GL/EGL/EGLContext.hpp"

#else

#error "Not support yet."

#endif
