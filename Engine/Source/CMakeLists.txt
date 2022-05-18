cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

if(DEFINED RING_BUILD_TEST)
    enable_testing()
endif()

project(Ring LANGUAGES C CXX)

if(${RING_BUILD_TEST})
    add_subdirectory(ThirdParty)
endif()

add_subdirectory(Runtime)
