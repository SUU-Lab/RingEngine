#==============================================================================
#     ThirdParty
#==============================================================================

# Prerequisites
set(RingThirdPartyPrerequisitesDirectory
    ${CMAKE_CURRENT_SOURCE_DIR}/Prerequisites
    PARENT_SCOPE
)

# GoogleTest
if(${RING_BUILD_TEST})

    option(BUILD_GMOCK "Builds the googlemock subproject" OFF)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

endif()

# glfw
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)

# glew
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glew ${CMAKE_CURRENT_BINARY_DIR}/glew)

# Vulkan-Headers
set(RingVulkanHppIncludeDirectories
    ${CMAKE_CURRENT_SOURCE_DIR}/Vulkan-Headers/include
    PARENT_SCOPE
)

# eigen
# EIGEN_DEFAULT_TO_ROW_MAJOR "Use row-major as default matrix storage order"
# EIGEN_MPL2_ONLY
set(RingEigenIncludeDirectories
    ${CMAKE_CURRENT_SOURCE_DIR}/eigen/Eigen
    PARENT_SCOPE
)
