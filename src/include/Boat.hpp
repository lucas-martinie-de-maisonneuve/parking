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

    BoatA::BoatInfo *getBoatAtPosition(int x, int y);

    std::vector<BoatA::BoatInfo> boats = {
        {'1', 0, 0, 2, true},
        {'2', 1, 2, 3, false},
        {'3', 4, 4, 2, true},
        {'4', 6, 1, 3, false},
        {'5', 3, 5, 2, false},
        {'6', 7, 4, 3, false}};
};

#endif // BOAT_HPP
