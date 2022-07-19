#pragma once

#include "Window.hpp"
#include "Renderer.hpp"
#include "GL4/GLContext.hpp"
#include <memory>

namespace ring {
inline namespace render {

class GLRenderer final : public Renderer
{
public:
    GLRenderer(const Window& window);
    ~GLRenderer();

    void Begin() override;
    void End() override;

private:
    std::unique_ptr<gl::Context> m_context;
};

} // inline namespace render
} // namespace ring
