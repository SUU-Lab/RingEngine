#include "Main.hpp"
#include "GL/GLRenderer.hpp"

namespace ring {

int Main(LaunchState* launchState)
{
#if RING_PLATFORM_WINDOWS || RING_PLATFORM_LINUX
    Window window({ 640, 480 }, "Render_Sample");

    GLRenderer glRenderer(window);

    while (window.Update())
    {
        glRenderer.Begin();

        glRenderer.End();
    }
#endif
    return 0;
}

} // namespace ring
