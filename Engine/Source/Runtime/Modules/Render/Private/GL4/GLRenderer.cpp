#include "GL4/GLRenderer.hpp"

namespace ring {
inline namespace render {

GLRenderer::GLRenderer(const Window& window)
    : m_context(std::make_unique<gl::Context>(window))
{}

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
