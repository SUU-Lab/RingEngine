#pragma once

#include "Window.hpp"
#include "GL/GL.hpp"

namespace ring {
inline namespace render {
namespace gl {

class WGLContext final
{
public:
    explicit WGLContext(const Window& window);
    ~WGLContext();

    void SwapBuffers();

private:
    HWND m_hWnd;
    HDC m_hDC;
    HGLRC m_hGLRC;
};

typedef WGLContext Context;

} // namespace gl
} // inline namespace render
} // namespace ring
