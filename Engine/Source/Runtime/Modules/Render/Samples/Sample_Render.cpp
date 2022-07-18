#include "Main.hpp"
#include "GL/GLRenderer.hpp"

namespace ring {

int Main()
{
    Window window({ 640, 480 }, "Render_Sample");

    GLRenderer glRenderer(window);

    while (window.Update())
    {
        glRenderer.Begin();

        glRenderer.End();
    }

    return 0;
}

} // namespace ring
