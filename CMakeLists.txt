cmake_minimum_required(VERSION 3.20)
set(OpenCV_DIR $ENV{OPENCV_DIR}) # replace with valid path

# Forbid in-source builds
if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR "In-source builds are not allowed. Please create a separate build directory and run CMake from there.")
endif()

set(PROJECT_NAME ASCII_VIDEO)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# to prevent this: https://stackoverflow.com/questions/7013309/visual-studio-debugger-error-unable-to-start-program-specified-file-cannot-be-f
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# get OpenCV on your machine
find_package(OpenCV)

file(GLOB_RECURSE SRCS
${CMAKE_SOURCE_DIR}/source/*.c
${CMAKE_SOURCE_DIR}/source/*.cpp
${CMAKE_SOURCE_DIR}/source/*.cc
${CMAKE_SOURCE_DIR}/source/*.h
${CMAKE_SOURCE_DIR}/source/*.hpp
)

if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    add_executable(${PROJECT_NAME} ${SRCS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
elseif(NOT OpenCV_FOUND)
    message(FATAL_ERROR "Could not find OpenCV on your machine.\nInstall it there: https://opencv.org/releases/ and add an enviroment variable named OPENCV_DIR with the path to your installation directory AND RESTART THE TERMINAL. If the issue presists, try this:\n1. Open ${CMAKE_SOURCE_DIR}/CMakeLists.txt\n2. Find line 2 and replace \$ENV{OPENCV_DIR} with the path to your OpenCV installation directory")
endif()
