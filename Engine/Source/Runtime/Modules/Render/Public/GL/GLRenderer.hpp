#pragma once

#if RING_PLATFORM_WINDOWS || RING_PLATFORM_LINUX
#include "Window.hpp"
#endif

#include "Renderer.hpp"
#include "GL/GLContext.hpp"
#include <memory>

namespace ring {
inline namespace render {

class GLRenderer final : public Renderer
{
public:
#if RING_PLATFORM_WINDOWS || RING_PLATFORM_LINUX
    GLRenderer(const Window& window);
#endif

#if RING_PLATFORM_ANDROID
    GLRenderer(ANativeWindow* window);
#endif

    ~GLRenderer();

    void Begin() override;
    void End() override;

private:
    std::unique_ptr<gl::Context> m_context;
};

} // inline namespace render
} // namespace ring
