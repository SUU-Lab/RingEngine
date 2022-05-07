cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE GoogleTest)

set(TARGET_NAME Ring_ThirdParty_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Ring::ThirdParty::${TARGET_NAME_BASE})

if(TARGET ${TARGET_NAME})
    RETURN()
endif()

project(${TARGET_NAME})

if(${CMAKE_CXX_STANDARD} LESS 11)
    message(FATAL_ERROR "GoogleTest requires at least C++11")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
