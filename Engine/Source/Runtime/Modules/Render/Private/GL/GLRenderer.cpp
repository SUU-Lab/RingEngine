#include "GL/GLRenderer.hpp"

namespace ring {
inline namespace render {

#if RING_PLATFORM_WINDOWS || RING_PLATFORM_LINUX
GLRenderer::GLRenderer(const Window& window)
    : m_context(std::make_unique<gl::Context>(window))
{}
#endif

#if RING_PLATFORM_ANDROID
GLRenderer::GLRenderer(ANativeWindow* window)
    : m_context(std::make_unique<gl::Context>(window))
{}
#endif

GLRenderer::~GLRenderer()
{}

void GLRenderer::Begin()
{
    glClearColor(0.0f, 0.125f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLRenderer::End()
{
    glFlush();
    m_context->SwapBuffers();
}

} // inline namespace render
} // namespace ring
