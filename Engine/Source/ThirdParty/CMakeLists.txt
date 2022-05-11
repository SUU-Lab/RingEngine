
option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)
