cmake_minimum_required(VERSION 3.15)
project(BoardGame)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Include GameMath.hpp
include_directories(${CMAKE_SOURCE_DIR}/../../include)

# Main executable
add_executable(BoardGame src/main.cpp src/BoardGame.cpp)

# Testing
# option(BUILD_TESTING "Build tests" ON)
# if(BUILD_TESTING)
#     add_subdirectory(test)
# endif()