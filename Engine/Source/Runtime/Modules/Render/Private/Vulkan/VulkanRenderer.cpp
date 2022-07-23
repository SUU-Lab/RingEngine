#include "Vulkan/VulkanRenderer.hpp"

// #define はつけないように注意！
VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

namespace ring {
inline namespace render {

VulkanRenderer::VulkanRenderer()
{
    VULKAN_HPP_DEFAULT_DISPATCHER.init(m_dynamicLoader.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr"));

    vk::InstanceCreateInfo ici;
    vk::Instance instance = vk::createInstance(ici);
    VULKAN_HPP_DEFAULT_DISPATCHER.init(instance);

    vk::PhysicalDevice physicalDevice;
    std::vector<vk::PhysicalDevice> physicalDevices = instance.enumeratePhysicalDevices();

    vk::DeviceCreateInfo dci;
    vk::Device device = physicalDevices[0].createDevice(dci);
    VULKAN_HPP_DEFAULT_DISPATCHER.init(device);
}

VulkanRenderer::~VulkanRenderer()
{

}

void VulkanRenderer::Begin()
{

}

void VulkanRenderer::End()
{

}

} // inline namespace render
} // namespace ring

