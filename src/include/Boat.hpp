#include <iostream>
#include <vector>
#include <string>

class Boats
{
public:
    char id;
    int x, y;
    int length;
    bool horizontal;

    Boats(char id, int x, int y, int length, bool horizontal)
        : id(id), x(x), y(y), length(length), horizontal(horizontal) {}

    virtual bool move(char direction, char grid[GRID_SIZE][GRID_SIZE]) = 0;

    virtual ~Boats() = default;
};

const int GRID_SIZE = 8;

class Boat
{

public:
    char id;
    int x, y;
    int length;
    bool orientation; // true = horizontal, false = vertical

    Boat(char id, int x, int y, int length, bool orientation);
    ~Boat();

    void grid();
    int checkNeighbour();
    int moveUp();
    int moveDown();
    int moveRight();
    int moveLeft();
};
