#pragma once

#if RING_PLATFORM_WINDOWS
#include "WGL/WGLContext.hpp"
#elif RING_PLATFORM_LINUX
#include "X11/X11Context.hpp"
#else
#error "Not support yet."
#endif
