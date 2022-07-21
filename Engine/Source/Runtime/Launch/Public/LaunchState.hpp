#pragma once

#if RING_PLATFORM_ANDROID

#include "Android/AndroidLaunchState.hpp"

#else

namespace ring {

struct GenericLaunchState
{

};

typedef GenericLaunchState LaunchState;

} // namespace ring

#endif
