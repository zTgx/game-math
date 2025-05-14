
## Project Structure

```
BoardGame/
├── CMakeLists.txt
├── README.md
├── build/
├── include/
│   ├── BoardGame.h
│   └── Position.h
├── src/
│   ├── BoardGame.cpp
│   └── main.cpp
```

-   `CMakeLists.txt`: CMake build file.
-   `README.md`: Project description and instructions.
-   `include/`: Header files for the project.
    -   `BoardGame.h`: Declaration of the [`BoardGame`](BoardGame/include/BoardGame.h) class.
    -   `Position.h`: (If applicable) Definition of a position class/struct.
-   `src/`: Source files for the project.
    -   `BoardGame.cpp`: Implementation of the [`BoardGame`](BoardGame/src/BoardGame.cpp) class.
    -   `main.cpp`: Main function to run the game.
-   `build/`: Directory where the build files are stored.

## Dependencies

-   Compiler: g++-13 or higher
-   CMake: 3.15 or higher
-   OS: Ubuntu 2404

## Build Instructions

1.  Create a build directory:

    ```bash
    mkdir build
    cd build
    ```

2.  Run CMake:

    ```bash
    cmake .. -DBUILD_TESTING=ON
    ```

3.  Build the project:

    ```bash
    make
    ```

## Usage

Run the executable:

```bash
./BoardGame
```

## BoardGame Description

The `BoardGame` is a simple game implemented in C++. The game is played on a 6x5 board. Each cell contains a card with a value from 0 to 11. The value 0 represents a "joker" card, which can be considered as any other card.

### Gameplay

The goal of the game is to have five or more consecutive cards with the same value (including jokers) in a row or column. When this condition is met, the cards are removed from the board, and new cards are added to fill the empty spaces.

### Winning Condition

A winning condition is triggered when there are 5 or more consecutive cards with the same value (including "赖子") in horizontal or vertical direction.

### Output

The program outputs the information of the winning blocks in the following format:

```
round value block_size
```

For example:

```
1 3 11
```

This means that in round 1, there is a winning block of value 3 with a size of 11.

## 中文描述

```
有一个 6×5 的棋盘，每个格子里放置一张牌，其值为整数，范围：0到11。其中：
数字 0 表示“赖子”，可以与任意数字视为相同。

当在某一轮中，存在 连续5个或以上相同的牌（包括赖子） 在横向或纵向上相连时，即触发获胜条件。这些牌将在这一轮结束前被标记为待消除

当一轮结束的时候，会把获胜的地方全部去掉，并且未消除的牌会依次掉落下去。掉落完成后，空着的位置调用 一个方法 getCard(int row, int col) 获取这个地方新的牌。
补充完整盘面后，进入下一轮。

结束条件：当没有获胜的时候结束。

返回值：
在第几轮获胜，获胜对应的元素，获胜对应块的大小。

例子：输入
1 2 3 1 2 3
1 2 3 1 2 3
1 1 1 1 2 3
2 3 3 3 2 3
2 2 0 0 0 0

第一个盘面会返回：
1 1 8
1 2 11
1 3 11
```