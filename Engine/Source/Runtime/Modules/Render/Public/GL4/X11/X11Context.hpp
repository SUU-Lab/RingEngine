#pragma once

#include "Window.hpp"
#include "GL4/GL.hpp"

namespace ring {
inline namespace render {
namespace gl {

class X11Context final
{
public:
    explicit X11Context(const Window& window);
    ~X11Context();

    void SwapBuffers();

private:
    GLXContext m_context;
    Display* m_display;
    ::Window m_window;
};

typedef X11Context Context;

} // namespace gl
} // inline namespace render
} // namespace ring
