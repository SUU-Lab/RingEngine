#pragma once

#if RING_PLATFORM_WINDOWS
#include <GL/glew.h>
#include <GL/wglew.h>
#endif

#if RING_PLATFORM_LINUX
#include <GL/glew.h>
#include <GL/glx.h>
#endif

#if RING_PLATFORM_ANDROID
#include <EGL/egl.h>
#include <GLES/gl.h>
#endif
