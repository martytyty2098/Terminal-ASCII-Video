set(OpenCV_DIR $ENV{OPENCV_DIR}) # replace with valid path

project(ASCII_VIDEO)
set(CMAKE_CXX_STANDARD 14)

set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS
"${CMAKE_SOURCE_DIR}/source/VideoPlayer/*.h"
"${CMAKE_SOURCE_DIR}/source/VideoPlayer/*.cpp"
"${CMAKE_SOURCE_DIR}/source/VideoPlayer/*.hpp"
"${CMAKE_SOURCE_DIR}/source/VideoPlayer/*.cc"
"${CMAKE_SOURCE_DIR}/source/VideoPlayer/*.c"
)

add_executable(ASCII_VIDEO ${SRCS})
