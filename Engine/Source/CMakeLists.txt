cmake_minimum_required(VERSION 3.20)

message(CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME})

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 20)
endif()
message(CMAKE_CXX_STANDARD="${CMAKE_CXX_STANDARD}")

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Android")
    set(CMAKE_CROSSCOMPILING_EMULATOR
            #"adb shell"
            "${CMAKE_CURRENT_SOURCE_DIR}/../Build/Android/Tools/TestRunner.bat"
    )
    set(CROSSCOMPILING_EMULATOR
            #"adb shell"
            "${CMAKE_CURRENT_SOURCE_DIR}/../Build/Android/Tools/TestRunner.bat"
            )
endif()
message(CMAKE_CROSSCOMPILING_EMULATOR="${CMAKE_CROSSCOMPILING_EMULATOR}")

message(CMAKE_COMMAND="${CMAKE_COMMAND}")

project(Ring LANGUAGES C CXX)

if(${RING_BUILD_TEST})
    enable_testing()
    message("enable testing")
endif()

if(${RING_BUILD_TEST})
    add_subdirectory(ThirdParty)
endif()

add_subdirectory(Runtime)
