#ifndef BOAT_HPP
#define BOAT_HPP

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BoatA
{
public:
    struct BoatInfo
    {
        char id; // 1 to 6
        int x, y;
        int length;      // 2 or 3
        bool horizontal; // true = H, false = V
    };

    int GridSize = 8;

    virtual bool move(char direction, char grid[8][8]) = 0;

    virtual ~BoatA() = default;
};

class Boat
{
public:
    const int ROWS = 8;
    const int COLS = 8;
    int squareSize = 50;
    int BoatRow = 4;
    int BoatCol = 4;

    vector<vector<int>> boatList;

    Boat();
    ~Boat();

    void grid();
    bool checkNeighbour(int row, int col, int distance, char direction);
    int moveU();
    int moveD();
    int moveR();
    int moveL();
};

#endif // BOAT_HPP
