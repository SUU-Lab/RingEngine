cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME Ring_Runtime_Test)

message("TEST: ${TARGET_NAME}")

project(${TARGET_NAME} LANGUAGES C CXX)

add_executable(${TARGET_NAME}
    "${PROJECT_SOURCE_DIR}/Test_Runtime.cpp"
)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Tests")
target_link_libraries(${TARGET_NAME} PRIVATE Ring::Runtime gtest_main gtest)

if (ANDROID)
    if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
#        add_custom_command(
#                TARGET ${TARGET_NAME}
#                PRE_BUILD
#                COMMAND ${CMAKE_SOURCE_DIR}/../Build/Android/Tools/MakeTestRunner ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}
#        )
        set_target_properties(
            ${TARGET_NAME}
            PROPERTIES
            CROSSCOMPILING_EMULATOR
            ${CMAKE_SOURCE_DIR}/../Build/Android/Tools/TestRunner.bat
        )
    else()
        set_target_properties(
            ${TARGET_NAME}
            PROPERTIES
            CROSSCOMPILING_EMULATOR
            ${CMAKE_SOURCE_DIR}/../Build/Android/Tools/test_runner.sh
        )
    endif()
endif()

include(GoogleTest)
gtest_discover_tests(
        ${TARGET_NAME}
        DISCOVERY_TIMEOUT 20
)
