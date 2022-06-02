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
    add_subdirectory(ThirdParty)
    include(GoogleTest)

    function(ring_discover_tests target)
        if(ANDROID)
            if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
                set(RING_CROSSCOMPILING_EMULATOR
                    ${CMAKE_SOURCE_DIR}/../Build/Android/Tools/TestRunner.bat
                )
            else()
                set(RING_CROSSCOMPILING_EMULATOR
                    ${CMAKE_SOURCE_DIR}/../Build/Android/Tools/test_runner.sh
                )
            endif()
            set_target_properties(
                ${target}
                PROPERTIES
                FOLDER "Tests"
                CROSSCOMPILING_EMULATOR ${RING_CROSSCOMPILING_EMULATOR}
            )
            gtest_discover_tests(
                ${target}
                DISCOVERY_TIMEOUT 20
                DISCOVERY_MODE PRE_TEST
            )
        else()
            gtest_discover_tests(
                ${target}
                DISCOVERY_TIMEOUT 20
            )
        endif()
    endfunction()
endif()

add_subdirectory(Runtime)
