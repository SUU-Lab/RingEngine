#==============================================================================
#     ThirdParty
#==============================================================================

if(${RING_BUILD_TEST})

    option(BUILD_GMOCK "Builds the googlemock subproject" OFF)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glew ${CMAKE_CURRENT_BINARY_DIR}/glew)

# Vulkan-Hpp
option (VULKAN_HPP_RUN_GENERATOR "Run the HPP generator" ON)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vulkan-Hpp ${CMAKE_CURRENT_BINARY_DIR}/Vulkan-Hpp)

set(RingVulkanHppIncludeDirectories
    ${CMAKE_CURRENT_SOURCE_DIR}/Vulkan-Hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vulkan-Hpp/Vulkan-Headers/include
    PARENT_SCOPE
)
