#pragma once

struct ANativeWindow;

namespace ring {

struct AndroidLaunchState {
    ANativeWindow* window;
};

typedef AndroidLaunchState LaunchState;

} // namespace ring

