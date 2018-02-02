#include "stdafx.h"
struct position
{
    int row;
    int col;
    position() :row(0), col(0) {}
    position(const position&);//复制构造函数
    void up() { row -= 1; return; }
    void down() { row += 1; return; }
    void left() { col -= 1; return; }
    void right() { col += 1; return; }
    void to(int thePositionNumber);
    position& operator=(const position& theElement);
    bool operator==(const position& theElement);
};
struct MazeGrid
{
    int ** data;
    int rows;
    int cols;
    MazeGrid(int theRows, int theCols, int ** theGrid) :rows(theRows), cols(theCols), data(theGrid) {}
    MazeGrid():rows(0), cols(0), data(nullptr) {};
    int& operator()(int row, int col) { return data[row][col]; }
    int& operator()(position thePosition) { return data[thePosition.row][thePosition.col]; }
};
class ShortestPathMaze
{
private:
    MazeGrid grid;
    position here;
    position start;
    position over;
    position neighbor;
    position* path;//指向最终的路径
    CircularArrayQuene<position> quene;
public:
    ShortestPathMaze(const MazeGrid& theGrid, const int startRow, const int startCol, const int overRow, const int overCol);
    bool solve();
    void output();
};

void position::to(int thePositionNumber)
{
    switch (thePositionNumber)
    {
    case 0:
        right();
        break;
    case 1:
        down();
        break;
    case 2:
        left();
        break;
    case 3:
        right();
        break;
    default:
        break;
    }
}
position& position::operator=(const position & theElement)
{
    row = theElement.row;
    col = theElement.col;
    return (*this);
}
bool position::operator==(const position & theElement)
{
    if (row == theElement.row && col == theElement.col)
        return true;
    else
        return false;
}
position::position(const position& theElement) 
{
    row = theElement.row;
    col = theElement.col;
}
ShortestPathMaze::ShortestPathMaze(const MazeGrid& theGrid, const int startRow, const int startCol, const int overRow, const int overCol)
{
    //增加外墙：
    grid.cols = theGrid.cols + 2;
    grid.rows = theGrid.rows + 2;
    //创建新的大一圈的二维数组
    (*grid.data) = new int[grid.rows];
    for (int i = 0; i < grid.rows; i++)
    {
        grid.data[i] = new int[grid.cols];
        fill(grid.data[i], grid.data[i] + grid.cols, 1);//整个数组填充1
    }
    //为新的二维数组赋值
    for (int i = 0; i < theGrid.rows; i++)
    {
        for (int j = 0; j < theGrid.cols; j++)
        {
            grid.data[i + 1][j + 1] = theGrid.data[i][j];
        }
    }
    start.row = startRow;
    start.col = startCol;
    over.row = overRow;
    over.col = overCol;
    path = nullptr;
}
bool ShortestPathMaze::solve()
{
    grid(start) = 2;
    here = start;
    if (here == over)
        return true;
    while (true)
    {        
        for (int i = 0; i < 4; i++)
        {
            neighbor = here;
            neighbor.to(i);
            if (grid(neighbor) == 0)
            {
                grid(neighbor) = grid(here) + 1;
                quene.push(neighbor);
            }
            if (neighbor == over)
                break;//已找到出口
        }
        if (neighbor == over)
            break;//已找到出口
        if (!quene.empty())
        {
            here = quene.pop();
        }
        else
            return false;
    }
    //已找到路径，开始回溯
    int pathLength = grid(over) - 2;
    path = new position[pathLength];
    for (int i = pathLength - 1; i >= 0; i--)
    {
        path[i] = here;
        for (int j = 0; j < 4; j++)
        {
            neighbor.to(i);
            if (grid(neighbor) == j + 2)
                break;
        }
        here = neighbor;
    }
    return true;
}