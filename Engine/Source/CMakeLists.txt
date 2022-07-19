cmake_minimum_required(VERSION 3.18.1)

if(NOT "${CMAKE_CXX_STANDARD}")

  set(CMAKE_CXX_STANDARD 20)

endif()

project(Ring LANGUAGES C CXX)

add_subdirectory(ThirdParty)

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


function(ring_add_executable)

    cmake_parse_arguments(
        MYFUNC
        ""
        ""
        "TARGET;PROPERTIES;COMPILE_OPTIONS;SOURCES;LIBRARIES;INCLUDE_DIRECTORIES"
        ${ARGN}
    )

    if(ANDROID)

        # android needs shared library
        add_library(
            ${MYFUNC_TARGET}
        
            SHARED
            $<TARGET_OBJECTS:Ring::Launch>
        )

        # export "ANativeActivity_onCreate"
        set_target_properties(
            ${MYFUNC_TARGET}

            PROPERTIES
            APPEND_STRING
            PROPERTY
            LINK_FLAGS " -u ANativeActivity_onCreate"
        )

    else()

        # executable
        add_executable(
            ${MYFUNC_TARGET}
            $<TARGET_OBJECTS:Ring::Launch>
        )

    endif()

    # sources
    target_sources(
        ${MYFUNC_TARGET}

        ${MYFUNC_SOURCES}
    )

    if(MYFUNC_INCLUDE_DIRECTORIES)

        # include directories
        target_include_directories(
            ${TARGET_NAME}

            ${MYFUNC_INCLUDE_DIRECTORIES}
        )

    endif()

    if (ANDROID)

        # library dependencies (android needs public?)
        target_link_libraries(
            ${MYFUNC_TARGET}

            PUBLIC
            Ring::Launch

            PRIVATE
            ${MYFUNC_LIBRARIES}
        )

    else()

        # library dependencies
        target_link_libraries(
            ${MYFUNC_TARGET}

            PRIVATE
            Ring::Launch
            ${MYFUNC_LIBRARIES}
        )

    endif()


    if(MYFUNC_PROPERTIES)

        # properties
        set_target_properties(
            ${MYFUNC_TARGET}

            PROPERTIES

            ${MYFUNC_PROPERTIES}
        )

    endif()

    if(MYFUNC_COMPILE_OPTIONS)

        # compile options
        target_compile_options(
            ${MYFUNC_TARGET}

            ${MYFUNC_COMPILE_OPTIONS}
        )

    endif()

endfunction() # ring_add_executable

add_subdirectory(Runtime)
