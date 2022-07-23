#include "Main.hpp"
#include "GL/GLRenderer.hpp"
#include "Vulkan/VulkanRenderer.hpp"

namespace ring {

int Main(LaunchState* launchState)
{
    VulkanRenderer vulkanRenderer;

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
