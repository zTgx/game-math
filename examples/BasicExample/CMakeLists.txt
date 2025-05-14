cmake_minimum_required(VERSION 3.10)
project(GameMathExample)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Eigen include directory
include_directories(${CMAKE_SOURCE_DIR}/../../)

# Add executable
add_executable(GameMathExample main.cpp)

# Find Eigen3 package
find_package(Eigen3 REQUIRED)

# Link against Eigen (header-only, so no linking needed, but good practice)
target_link_libraries(GameMathExample Eigen3::Eigen) # If Eigen was a library