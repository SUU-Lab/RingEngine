﻿#pragma once

#ifndef STRICT
#define STRICT
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX) && defined(_MSC_VER)
#define NOMINMAX
#endif

#include <tchar.h>
#include <Windows.h>
#include <crtdbg.h>
