#pragma once

#include "GL/GL.hpp"

namespace ring {
inline namespace render {
namespace gl {

class EGL final
{
public:
    static constexpr ::EGLDisplay NO_DISPLAY = EGL_NO_DISPLAY;
    static constexpr ::EGLSurface NO_SURFACE = EGL_NO_SURFACE;
    static constexpr ::EGLContext NO_CONTEXT = EGL_CAST(::EGLContext, 0);
};

} // namespace gl
} // inline namespace render
} // namespace ring
