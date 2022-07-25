#include "GL/WGL/WGLContext.hpp"
#include <cassert>

namespace ring {
inline namespace render {
namespace gl {

WGLContext::WGLContext(const Window& window)
    : m_hWnd(window.GetNativeHandle())
    , m_hDC(::GetDC(m_hWnd))
    , m_hGLRC(nullptr)
{
    //OpenGLが使用可能なピクセルフォーマットを取得
    PIXELFORMATDESCRIPTOR pfdesc;
    ZeroMemory(&pfdesc, sizeof(pfdesc));
    pfdesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfdesc.nVersion = 1;
    pfdesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfdesc.iPixelType = PFD_TYPE_RGBA;
    pfdesc.cColorBits = 32;
    pfdesc.cDepthBits = 24;
    pfdesc.cStencilBits = 8;
    int format = ChoosePixelFormat(m_hDC, &pfdesc);

    assert(format != 0 && "ChoosePixelFormat() is failed.");

    SetPixelFormat(m_hDC, format, &pfdesc);

    m_hGLRC = wglCreateContext(m_hDC);
    wglMakeCurrent(m_hDC, m_hGLRC);
}

WGLContext::~WGLContext()
{
    ::wglDeleteContext(m_hGLRC);
    ::ReleaseDC(m_hWnd, m_hDC);
}

void WGLContext::SwapBuffers()
{
    ::SwapBuffers(m_hDC);
}

} // namespace gl
} // inline namespace render
} // namespace ring
