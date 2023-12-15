project(VIDEO_SEEKER)
set(CMAKE_CXX_STANDARD 14)

set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# to prevent this: https://stackoverflow.com/questions/7013309/visual-studio-debugger-error-unable-to-start-program-specified-file-cannot-be-f
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS
"${CMAKE_SOURCE_DIR}/source/VideoSeeker/*.h"
"${CMAKE_SOURCE_DIR}/source/VideoSeeker/*.cpp"
"${CMAKE_SOURCE_DIR}/source/VideoSeeker/*.hpp"
"${CMAKE_SOURCE_DIR}/source/VideoSeeker/*.cc"
"${CMAKE_SOURCE_DIR}/source/VideoSeeker/*.c"
)

add_executable(VIDEO_SEEKER ${SRCS})