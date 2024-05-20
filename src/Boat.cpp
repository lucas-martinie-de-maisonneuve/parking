#include <iostream>
#include "Boat.hpp"
using namespace std;

vector<vector<int>> boatList(8, vector<int>(8, false));

Boat::Boat() : boatList(ROWS, vector<int>(COLS, 0)), BoatRow(1), BoatCol(2)
{
    boatList[BoatRow][BoatCol] = 1; // Example initialization, adjust as necessary

    // Initialize boats
    boats = {
        {'1', 0, 0, 2, true},
        {'2', 1, 2, 3, false},
        {'3', 4, 4, 2, true},
        {'4', 6, 1, 3, false},
        {'5', 3, 5, 2, false},
        {'6', 7, 4, 3, false}};

    for (const auto &boat : boats)
    {
        if (boat.horizontal)
        {
            for (int i = 0; i < boat.length; ++i)
            {
                boatList[boat.y][boat.x + i] = 1; // Mark horizontal boat positions
            }
        }
        else
        {
            for (int i = 0; i < boat.length; ++i)
            {
                boatList[boat.y + i][boat.x] = 1; // Mark vertical boat positions
            }
        }
    }
}

Boat::~Boat()
{
}

void Boat::moveUp(char id)
{
    for (auto &boat : boats)
    {
        if (boat.id == id)
        {
            boat.y -= 1;
            break;
        }
    }
}

void Boat::moveDown(char id)
{
    for (auto &boat : boats)
    {
        if (boat.id == id)
        {
            boat.y += 1;
            break;
        }
    }
}

void Boat::moveLeft(char id)
{
    for (auto &boat : boats)
    {
        if (boat.id == id)
        {
            boat.x -= 1;
            break;
        }
    }
}

void Boat::moveRight(char id)
{
    for (auto &boat : boats)
    {
        if (boat.id == id)
        {
            cout << boat.x << "  " << boat.y << endl;
            boat.x += 1;
            cout << boat.x << "  " << boat.y << endl;

            break;
        }
    }
}

BoatA::BoatInfo *Boat::getBoatAtPosition(int x, int y)
{
    for (auto &boat : boats)
    {
        if (boat.horizontal)
        {
            if (y == boat.y && x >= boat.x && x < boat.x + boat.length)
            {
                return &boat;
            }
        }
        else
        {
            if (x == boat.x && y >= boat.y && y < boat.y + boat.length)
            {
                return &boat;
            }
        }
    }
    return nullptr;
}
