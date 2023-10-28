#pragma once
#include "grid.h"
#include "blocks.cpp"
class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    void RotateBlock();
    bool gameOver;
    int score;
    Music music;

private:
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    bool isBlockOutside();
    void LockBlock();
    bool BlockFits();
    void Rotate();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Grid grid;
    Sound rotateSound;
    Sound clearSound;
};