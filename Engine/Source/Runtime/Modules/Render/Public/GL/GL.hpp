#pragma once

#if RING_PLATFORM_WINDOWS
#include <gl/GL.h>
#endif

#if RING_PLATFORM_LINUX
#define GLX_GLXEXT_PROTOTYPES
#include <GL/glx.h>
#include <GL/glxext.h>
#endif
