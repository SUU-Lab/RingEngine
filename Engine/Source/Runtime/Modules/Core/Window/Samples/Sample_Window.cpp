#include "Window.hpp"

namespace ring {

int Main()
{
    ring::Window window({ 640, 480 }, "Sample_Window");

    while (window.Update())
    {
    }

    return 0;
}

} // namespace ring
