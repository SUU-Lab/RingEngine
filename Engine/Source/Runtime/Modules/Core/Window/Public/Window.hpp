#pragma once

#ifdef RING_PLATFORM_WINDOWS

#include "Windows/WindowsWindow.hpp"

#elif RING_PLATFORM_LINUX

#include "Linux/LinuxWindow.hpp"

#else

#error "Platform is not supported yet."

#endif
