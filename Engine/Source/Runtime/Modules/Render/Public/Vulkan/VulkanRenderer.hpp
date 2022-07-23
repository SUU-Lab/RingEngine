#pragma once

#include "Renderer.hpp"
#include "Vulkan/VulkanPrerequisites.hpp"

namespace ring {
inline namespace render {

class VulkanRenderer final : public Renderer
{
public:
    VulkanRenderer();
    ~VulkanRenderer();

    void Begin() override;
    void End() override;

private:
    vk::DynamicLoader m_dynamicLoader;
};

} // inline namespace render
} // namespace ring
