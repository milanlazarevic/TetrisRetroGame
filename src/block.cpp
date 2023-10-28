#include "block.h"
#include "colors.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffSet = 0;
    colOffSet = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = getCellPositions();
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}
void Block::Move(int rows, int columns)
{
    rowOffSet += rows;
    colOffSet += columns;
}

std::vector<Position> Block::getCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for (Position tile : tiles)
    {
        Position newPos = Position(tile.row + rowOffSet, tile.column + colOffSet);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}
void Block::Rotate()
{
    rotationState++;
    if (rotationState == cells.size())
    {
        rotationState = 0;
    }
}
void Block::UndoRotation()
{
    rotationState--;
    if (rotationState == -1)
    {
        rotationState = cells.size() - 1;
    }
}