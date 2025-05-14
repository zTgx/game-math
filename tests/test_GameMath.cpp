#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>
#include "../GameMath.hpp"

TEST_CASE("Matrix rotation", "[matrix]") {
    GameMath::Matrix<int> mat = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    auto rotated = GameMath::rotate_90_clockwise(mat);
    
    REQUIRE(rotated.rows() == 3);
    REQUIRE(rotated.cols() == 2);
    REQUIRE(rotated(0, 0) == 4);
    REQUIRE(rotated(0, 1) == 1);
}