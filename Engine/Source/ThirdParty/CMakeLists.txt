#==============================================================================
#     ThirdParty
#==============================================================================

# GoogleTest
if(${RING_BUILD_TEST})

    option(BUILD_GMOCK "Builds the googlemock subproject" OFF)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

endif()

# glew
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glew ${CMAKE_CURRENT_BINARY_DIR}/glew)

# Vulkan-Headers
set(RingVulkanHppIncludeDirectories
    ${CMAKE_CURRENT_SOURCE_DIR}/Vulkan-Headers/include
    PARENT_SCOPE
)
