cmake_minimum_required(VERSION 3.20)

# Forbid in-source builds
if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR "In-source builds are not allowed. Please create a separate build directory and run CMake from there.")
endif()

project(MASTER)

set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${CMAKE_SOURCE_DIR}/source/VideoSeeker)
add_subdirectory(${CMAKE_SOURCE_DIR}/source/VideoPlayer)