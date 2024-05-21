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
        char id;
        int x, y;
        int length;
        bool horizontal;
    };

    virtual ~BoatA() = default;

    virtual void moveUp(char id) = 0;
    virtual void moveDown(char id) = 0;
    virtual void moveLeft(char id) = 0;
    virtual void moveRight(char id) = 0;
};

class Boat : public BoatA
{
public:
    const int ROWS = 8;
    const int COLS = 8;
    int squareSize = 50;
    int BoatRow = 4;
    int BoatCol = 4;

    Boat();
    ~Boat();
    void moveUp(char id) override;
    void moveDown(char id) override;
    void moveLeft(char id) override;
    void moveRight(char id) override;
    bool isPositionOccupied(int x, int y, char id) const;

    BoatA::BoatInfo *getBoatAtPosition(int x, int y);

    std::vector<BoatA::BoatInfo> boats;

    bool gameOver = false;
    bool gameAnimation = false;
};

#endif // BOAT_HPP
