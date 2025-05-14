cmake_minimum_required(VERSION 3.15)
project(BoardGame)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Include GameMath.hpp
include_directories(${CMAKE_SOURCE_DIR}/../../)

# Main executable
add_executable(BoardGame src/main.cpp src/BoardGame.cpp)

# Find Eigen3 package
find_package(Eigen3 REQUIRED)

# Link against Eigen (header-only, so no linking needed, but good practice)
target_link_libraries(BoardGame Eigen3::Eigen) # If Eigen was a library

# Testing
# option(BUILD_TESTING "Build tests" ON)
# if(BUILD_TESTING)
#     add_subdirectory(test)
# endif()