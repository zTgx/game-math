#include "BoardGame.h"
#include <iostream>
#include <queue>

BoardGame::BoardGame(int rows, int cols) : ROWS(rows), COLS(cols) {
    board.resize(ROWS, std::vector<int>(COLS, 0));
}

void BoardGame::setBoard(const std::vector<std::vector<int>>& b) {
    board = b;
}

int BoardGame::getCard(int row, int col) {
    // 补牌函数示例，固定返回1，可根据需求修改
    return 1;
}

bool BoardGame::isSame(int a, int b) {
    return a == LAIZI || b == LAIZI || a == b;
}

void BoardGame::bfs(int r, int c, int val, std::vector<std::vector<bool>>& visited,
                    std::vector<std::pair<int,int>>& comp) {
    // 方向向量: 向下	-> 向上	-> 向右	-> 向左
    static const int dr[4] = {1, -1, 0, 0};
    static const int dc[4] = {0, 0, 1, -1};

    std::queue<std::pair<int,int>> q;
    q.emplace(r,c);
    visited[r][c] = true;

    // 连通块集合
    comp.push_back({r,c});

    while(!q.empty()) {
        auto cur = q.front(); q.pop();

        int cr = cur.first, cc = cur.second;

        // 遍历四个方向
        for(int d = 0; d < 4; ++d) {
            int nr = cr + dr[d], nc = cc + dc[d];
            if(nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) continue;
            if(visited[nr][nc]) continue;
            if(board[nr][nc] == val || board[nr][nc] == LAIZI) {
                visited[nr][nc] = true;
                comp.push_back({nr,nc});
                q.emplace(nr,nc);
            }
        }
    }
}

void BoardGame::play() {
    int round = 0;
    ++round;

    std::map<int, std::set<std::pair<int,int>>> winBlocks;

    // 对每个数字1~11做连通块搜索
    for(int val = 1; val <= 11; ++val) {
        std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLS, false));
        for(int r = 0; r < ROWS; ++r) {
            for(int c = 0; c < COLS; ++c) {
                if(!visited[r][c] && (board[r][c] == val || board[r][c] == LAIZI)) {
                    std::vector<std::pair<int,int>> comp;
                    bfs(r, c, val, visited, comp);
                    if((int)comp.size() >= 5) {
                        for(auto &p : comp) {
                            winBlocks[val].insert(p);
                        }
                    }
                }
            }
        }
    }

    if(winBlocks.empty()) {
        // 无获胜块，结束
        return;
    }

    // 输出获胜块信息
    for(auto &kv : winBlocks) {
        std::cout << round << " " << kv.first << " " << kv.second.size() << "\n";
    }

    // 标记消除
    std::vector<std::vector<bool>> toRemove(ROWS, std::vector<bool>(COLS, false));
    for(auto &kv : winBlocks) {
        for(auto &p : kv.second) {
            toRemove[p.first][p.second] = true;
        }
    }

    // 消除并下落补牌
    for(int c = 0; c < COLS; ++c) {
        std::vector<int> colCards;
        for(int r = 0; r < ROWS; ++r) {
            if(!toRemove[r][c]) colCards.push_back(board[r][c]);
        }
        int newCount = ROWS - (int)colCards.size();
        std::vector<int> newCol;
        for(int i = 0; i < newCount; ++i) newCol.push_back(getCard(i, c));
        for(int v : colCards) newCol.push_back(v);
        for(int r = 0; r < ROWS; ++r) board[r][c] = newCol[r];
    }
}
