#pragma once

#ifdef RING_PLATFORM_WINDOWS

#include "Windows/WindowsWindow.hpp"

#elif RING_PLATFORM_LINUX

#include "X11/X11Window.hpp"

#else

#error "Platform is not supported yet."

#endif
