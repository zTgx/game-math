#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <vector>
#include <set>
#include <map>

class BoardGame {
public:
    BoardGame(int rows, int cols);

    void setBoard(const std::vector<std::vector<int>>& board);
    void play();

private:
    int ROWS, COLS;
    const int LAIZI = 0;
    std::vector<std::vector<int>> board;

    int getCard(int row, int col);
    bool isSame(int a, int b);
    void bfs(int r, int c, int val, std::vector<std::vector<bool>>& visited,
             std::vector<std::pair<int,int>>& comp);
};
#endif
