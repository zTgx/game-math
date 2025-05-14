cmake_minimum_required(VERSION 3.10)
project(GameMathExample)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Eigen include directory
include_directories(${CMAKE_SOURCE_DIR}/../../include)

# Add executable
add_executable(GameMathExample main.cpp)
