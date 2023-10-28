#include "grid.h"
#include <iostream>
#include "colors.h"
// implementation file
Grid::Grid()
{
    numCols = 10;
    numRows = 20;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            grid[row][col] = 0;
        }
    }
}

void Grid::Print()
{
    for (int row = 0; row <= numRows; row++)
    {
        for (int col = 0; col <= numCols; col++)
        {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}
bool Grid::IsCellOutside(int row, int col)
{
    if (row >= 0 && row < numRows && col < numCols && col >= 0)
    {
        return false;
    }
    return true;
}
bool Grid::isCellEmpty(int row, int col)
{
    if (grid[row][col] == 0)
    {
        return true;
    }
    return false;
}
bool Grid::IsRowFull(int row)
{
    for (int cell : grid[row])
    {
        if (cell == 0)
        {
            return false;
        }
    }
    return true;
}
void Grid::ClearRow(int row)
{
    for (int cell : grid[row])
    {
        cell = 0;
    }
}
void Grid::MoveRowDown(int row, int numRows)
{
    for (int column = 0; column < numCols; column++)
    {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}
int Grid::ClearFullRows()
{
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            completed++;
            ClearRow(row);
        }
        else if (completed)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}