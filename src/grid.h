#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
    Grid();
    void Print();
    void Initialize();
    void Draw();
    bool isCellEmpty(int row, int column);
    bool IsCellOutside(int row, int col);
    int ClearFullRows();
    int grid[20][10];

private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};