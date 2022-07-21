#include "GL/EGL/EGLContext.hpp"
#include <memory>

namespace ring {
inline namespace render {
namespace gl {

EGLContext::EGLContext(ANativeWindow* window)
{
    const ::EGLint attributes[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    ::EGLint w, h, format;
    ::EGLint numConfigs;
    ::EGLConfig config = nullptr;
    ::EGLSurface surface;
    ::EGLContext context;

    ::EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, nullptr, nullptr);

    eglChooseConfig(display, attributes, nullptr,0, &numConfigs);
    std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
    assert(supportedConfigs);
    eglChooseConfig(display, attributes, supportedConfigs.get(), numConfigs, &numConfigs);
    assert(numConfigs);
    auto i = 0;
    for (; i < numConfigs; i++)
    {
        auto& cfg = supportedConfigs[i];
        EGLint r, g, b, d;
        if (eglGetConfigAttrib(display, cfg, EGL_RED_SIZE, &r)   &&
            eglGetConfigAttrib(display, cfg, EGL_GREEN_SIZE, &g) &&
            eglGetConfigAttrib(display, cfg, EGL_BLUE_SIZE, &b)  &&
            eglGetConfigAttrib(display, cfg, EGL_DEPTH_SIZE, &d) &&
            r == 8 && g == 8 && b == 8 && d == 0 ) {

            config = supportedConfigs[i];
            break;
        }
    }

    if (i == numConfigs)
    {
        config = supportedConfigs[0];
    }

    if (config == nullptr)
    {
        assert(false && "Unable to initialize EGLConfig");
    }

    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    surface = eglCreateWindowSurface(display, config, window, nullptr);
    context = eglCreateContext(display, config, nullptr, nullptr);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
    {
        assert(false && "Unable to eglMakeCurrent");
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    m_display = display;
    m_context = context;
    m_surface = surface;
    m_width = w;
    m_height = h;

    // Check openGL on the system
//    auto opengl_info = {GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS};
//    for (auto name : opengl_info) {
//        auto info = glGetString(name);
//        LOGI("OpenGL Info: %s", info);
//    }

    // Initialize GL state.
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);
}

EGLContext::~EGLContext()
{
    if (m_display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(m_display, EGL::NO_SURFACE, EGL::NO_SURFACE, EGL::NO_CONTEXT);
        if (m_context != EGL::NO_CONTEXT)
        {
            eglDestroyContext(m_display, m_context);
        }
        eglTerminate(m_display);
    }

    m_display = EGL::NO_DISPLAY;
    m_surface = EGL::NO_SURFACE;
    m_context = EGL::NO_CONTEXT;
}

void EGLContext::SwapBuffers()
{
    eglSwapBuffers(m_display, m_surface);
}

} // namespace gl
} // inline namespace render
} // namespace ring