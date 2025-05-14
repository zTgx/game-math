cmake_minimum_required(VERSION 3.15)

# For Catch2 (if using)
find_package(Catch2 REQUIRED)

# Add test executable
add_executable(test_GameMath test_GameMath.cpp)

# Link test executable with your library and testing framework
target_link_libraries(test_GameMath 
    PRIVATE 
    GameMath
    Catch2::Catch2WithMain  # If using Catch2
)

# Register as test
enable_testing()
add_test(NAME test_GameMath COMMAND test_GameMath)

# Find Eigen3 package
find_package(Eigen3 REQUIRED)
target_link_libraries(test_GameMath PUBLIC Eigen3::Eigen) # If Eigen was a library
