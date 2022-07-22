#include "LaunchState.hpp"
#include "Window.hpp"

namespace ring {

int Main(LaunchState*)
{
    ring::Window window({ 640, 480 }, "Sample_Window");

    while (window.Update())
    {
    }

    return 0;
}

} // namespace ring
