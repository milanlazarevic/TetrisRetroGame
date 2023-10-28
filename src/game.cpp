#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("../sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("../sounds/rotate.mp3");
    clearSound = LoadSound("../sounds/clear.mp3");
}
Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}
std::vector<Block> Game::GetAllBlocks()
{

    return {IBlock(), JBlock(), TBlock(), LBlock(), OBlock(), SBlock(), ZBlock()};
}
void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;

    default:
        nextBlock.Draw(270, 270);
        break;
    }
}
void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed)
    {
        gameOver = false;
        Reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_UP:
        RotateBlock();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0, 1);
        break;

    default:
        break;
    }
}
void Game::MoveBlockLeft()
{
    if (!gameOver)
    {

        currentBlock.Move(0, -1);
        if (isBlockOutside() || !BlockFits())
        {
            currentBlock.Move(0, 1);
        }
    }
}
void Game::MoveBlockRight()
{
    if (!gameOver)
    {

        currentBlock.Move(0, 1);
        if (isBlockOutside() || !BlockFits())
        {
            currentBlock.Move(0, -1);
        }
    }
}
void Game::MoveBlockDown()
{
    if (!gameOver)
    {

        currentBlock.Move(1, 0);
        if (isBlockOutside() || !BlockFits())
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}
void Game::RotateBlock()
{
    if (!gameOver)
    {

        currentBlock.Rotate();
        if (isBlockOutside() || !BlockFits())
        {
            currentBlock.UndoRotation();
        }
        else
        {
            PlaySound(rotateSound);
        }
    }
}
bool Game::isBlockOutside()
{
    std::vector<Position> elements = currentBlock.getCellPositions();
    for (Position item : elements)
    {

        if (grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}
void Game::Rotate()
{
    currentBlock.Rotate();
}
void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (!BlockFits())
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared)
    {
        PlaySound(clearSound);
    }
    UpdateScore(rowsCleared, 0);
}
bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        if (!grid.isCellEmpty(item.row, item.column))
        {
            return false;
        }
    }
    return true;
}
void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}
void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 200;
        break;
    case 3:
        score += 500;
        break;

    default:
        break;
    }
    score += moveDownPoints;
}