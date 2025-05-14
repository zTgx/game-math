#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>
#include "../include/GameMath/Matrix.hpp"
#include "../include/GameMath/Vector.hpp"

TEST_CASE("Matrix Rotation Operations", "[matrix][rotation]") {
    GameMath::Matrix<int, 2, 3> mat = {
        {1, 2, 3},
        {4, 5, 6}
    };

    SECTION("90-degree clockwise rotation") {
        auto rotated = rotate_90_clockwise(mat);
        
        REQUIRE(rotated.numRows() == 3);
        REQUIRE(rotated.numCols() == 2);
        REQUIRE(rotated[0][0] == 4);
        REQUIRE(rotated[0][1] == 1);
        REQUIRE(rotated[1][0] == 5);
        REQUIRE(rotated[1][1] == 2);
        REQUIRE(rotated[2][0] == 6);
        REQUIRE(rotated[2][1] == 3);
    }

    SECTION("90-degree counterclockwise rotation") {
        auto rotated = rotate_90_counterclockwise(mat);
        
        REQUIRE(rotated.numRows() == 3);
        REQUIRE(rotated.numCols() == 2);
        REQUIRE(rotated[0][0] == 3);
        REQUIRE(rotated[0][1] == 6);
        REQUIRE(rotated[1][0] == 2);
        REQUIRE(rotated[1][1] == 5);
        REQUIRE(rotated[2][0] == 1);
        REQUIRE(rotated[2][1] == 4);
    }

    SECTION("180-degree rotation") {
        auto rotated = rotate_180(mat);
        
        REQUIRE(rotated.numRows() == 2);
        REQUIRE(rotated.numCols() == 3);
        REQUIRE(rotated[0][0] == 6);
        REQUIRE(rotated[0][1] == 5);
        REQUIRE(rotated[0][2] == 4);
        REQUIRE(rotated[1][0] == 3);
        REQUIRE(rotated[1][1] == 2);
        REQUIRE(rotated[1][2] == 1);
    }
}

TEST_CASE("Matrix Flip Operations", "[matrix][flip]") {
    GameMath::Matrix<int, 3, 3> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    SECTION("Horizontal flip") {
        auto flipped = flip_horizontal(mat);
        
        REQUIRE(flipped[0][0] == 3);
        REQUIRE(flipped[0][1] == 2);
        REQUIRE(flipped[0][2] == 1);
        REQUIRE(flipped[1][0] == 6);
        REQUIRE(flipped[1][1] == 5);
        REQUIRE(flipped[1][2] == 4);
    }

    SECTION("Vertical flip") {
        auto flipped = flip_vertical(mat);
        
        REQUIRE(flipped[0][0] == 7);
        REQUIRE(flipped[0][1] == 8);
        REQUIRE(flipped[0][2] == 9);
        REQUIRE(flipped[1][0] == 4);
        REQUIRE(flipped[1][1] == 5);
        REQUIRE(flipped[1][2] == 6);
    }
}