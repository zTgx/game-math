#include <iostream>
#include "BoardGame.h"
#include <GameMath.hpp>

int main() {
    GameMath::Matrix<int> originalBoard = {
        {1, 2, 3, 1, 2, 3},
        {1, 2, 3, 1, 2, 3},
        {1, 1, 1, 1, 2, 3},
        {2, 3, 3, 3, 2, 3},
        {2, 2, 0, 0, 0, 0}
    };

    auto rotated = GameMath::rotate_90_clockwise(originalBoard);

    std::vector<std::vector<int>> result(rotated.rows(), std::vector<int>(rotated.cols()));

    for (int i = 0; i < rotated.rows(); ++i) {
        for (int j = 0; j < rotated.cols(); ++j) {
            result[i][j] = rotated(i, j);
        }
    }

    // std::cout << "rotated:\n";
    // for (const auto& row : result) {
    //     for (const auto& val : row) {
    //         std::cout << val << " ";
    //     }
    //     std::cout << "\n";
    // }

    BoardGame game(6, 5);
    game.setBoard(result);
    game.play();
    
    return 0;
}
