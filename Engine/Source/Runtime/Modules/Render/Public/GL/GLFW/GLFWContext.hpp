#pragma once

#include "GL/GL.hpp"
#include "Window.hpp"

namespace ring {
inline namespace render {
namespace gl {

class GLFWContext final
{
public:
    explicit GLFWContext(const Window& window);
    ~GLFWContext();

    void SwapBuffers();

private:
    ::GLFWwindow* m_window;
};

typedef GLFWContext Context;

} // namespace gl
} // inline namespace render
} // namespace ring
