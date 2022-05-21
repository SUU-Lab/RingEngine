cmake_minimum_required(VERSION 3.20)

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 20)
endif()

enable_testing()

project(Ring LANGUAGES C CXX)

add_subdirectory(ThirdParty)
add_subdirectory(Runtime)
