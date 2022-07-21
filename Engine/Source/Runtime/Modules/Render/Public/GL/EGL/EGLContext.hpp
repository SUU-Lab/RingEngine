#pragma once

#include "EGL.hpp"

struct ANativeWindow;

namespace ring {
inline namespace render {
namespace gl {

class EGLContext final
{
public:
    explicit EGLContext(ANativeWindow* window);
    ~EGLContext();

    void SwapBuffers();

private:
    ::EGLDisplay m_display = EGL::NO_DISPLAY;
    ::EGLSurface m_surface = EGL::NO_SURFACE;
    ::EGLContext m_context = EGL::NO_CONTEXT;
    int m_width = 0;
    int m_height = 0;
};

typedef EGLContext Context;

} // namespace gl
} // inline namespace render
} // namespace ring
