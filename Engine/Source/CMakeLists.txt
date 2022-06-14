cmake_minimum_required(VERSION 3.18.1)

if(NOT "${CMAKE_CXX_STANDARD}")

  set(CMAKE_CXX_STANDARD 20)

endif()

project(Ring LANGUAGES C CXX)

if(${RING_BUILD_TEST})

    if(${CMAKE_CXX_STANDARD} LESS 11)

        message(FATAL_ERROR "GoogleTest requires at least C++11")

    endif()

    if(ANDROID)
        if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Windows")

            string(
                REPLACE
                "/"
                "\\"
                RING_CMAKE_BINARY_DIR
                ${CMAKE_BINARY_DIR}
            )

        else()

            string(
                REPLACE
                "\\"
                "/"
                RING_CMAKE_BINARY_DIR
                ${CMAKE_BINARY_DIR}
            )

        endif()

        file(
            WRITE
            ${CMAKE_SOURCE_DIR}/../Build/Android/${ANDROID_ABI}/cmake_binary_dir.txt
            ${RING_CMAKE_BINARY_DIR})
    endif()

    enable_testing()

    add_subdirectory(ThirdParty)
    
    include(GoogleTest)

    # ring_discover_tests
    function(ring_discover_tests)

        cmake_parse_arguments(
            MYFUNC
            ""
            ""
            "TARGET;SOURCES;LIBRARIES"
            ${ARGN}
        )

        add_executable(
            ${MYFUNC_TARGET}
            ${MYFUNC_SOURCES}
        )

        target_link_libraries(
            ${MYFUNC_TARGET}
            PRIVATE
            ${MYFUNC_LIBRARIES} GTest::gtest GTest::gtest_main
        )

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
                ${MYFUNC_TARGET}
                PROPERTIES
                FOLDER "Tests"
                CROSSCOMPILING_EMULATOR ${RING_CROSSCOMPILING_EMULATOR}
            )

            gtest_discover_tests(
                ${MYFUNC_TARGET}
                DISCOVERY_TIMEOUT 20
                DISCOVERY_MODE PRE_TEST
            )

        else()

            gtest_discover_tests(
                ${MYFUNC_TARGET}
                DISCOVERY_TIMEOUT 20
            )

        endif()

    endfunction() # ring_discover_tests

endif()

add_subdirectory(Runtime)
