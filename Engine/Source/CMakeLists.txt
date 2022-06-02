cmake_minimum_required(VERSION 3.18.1)

message(CMAKE_HOST_SYSTEM_NAME=${CMAKE_HOST_SYSTEM_NAME})
message(CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME})

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 20)
endif()
message(CMAKE_CXX_STANDARD="${CMAKE_CXX_STANDARD}")

project(Ring LANGUAGES C CXX)

if(${RING_BUILD_TEST})
    enable_testing()
    message("enable testing")
endif()

if(${RING_BUILD_TEST})
    add_subdirectory(ThirdParty)
endif()

add_subdirectory(Runtime)
