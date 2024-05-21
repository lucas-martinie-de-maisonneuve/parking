#include <iostream>
#include "Boat.hpp"
using namespace std;

Boat::Boat() : BoatRow(1), BoatCol(2)
{
    // Initialize boats
    boats = {
        {'1', 0, 0, 2, true},
        {'2', 2, 3, 3, false},
        {'3', 4, 4, 2, true},
        {'4', 6, 2, 3, false},
        {'5', 3, 5, 2, false},
        {'6', 7, 4, 3, false},
        {'s', 0, 3, 2, true}, // Special boat
        {'7', 4, 1, 3, false},
        {'8', 5, 0, 3, true},
        {'9', 4, 6, 3, true},
        {'a', 0, 6, 2, false},
        {'b', 3, 1, 3, false},
        {'c', 5, 1, 3, true}};
}
Boat::~Boat()
{
}
void Boat::moveUp(char id)
{
    for (auto &boat : boats)
    {
        if (boat.id == id && boat.y > 0)
        {
            bool canMove = true;
            if (boat.horizontal)
            {
                for (int i = 0; i < boat.length; ++i)
                {
                    if (isPositionOccupied(boat.x + i, boat.y - 1, id))
                    {
                        canMove = false;
                        break;
                    }
                }
            }
            else
            {
                if (isPositionOccupied(boat.x, boat.y - 1, id))
                {
                    canMove = false;
                }
            }

            if (canMove)
            {
                boat.y -= 1;
            }
            break;
        }
    }
}

void Boat::moveDown(char id)
{
    for (auto &boat : boats)
    {
        if (boat.id == id && (boat.y + boat.length - 1) < ROWS - 1)
        {
            bool canMove = true;
            if (boat.horizontal)
            {
                for (int i = 0; i < boat.length; ++i)
                {
                    if (isPositionOccupied(boat.x + i, boat.y + 1, id))
                    {
                        canMove = false;
                        break;
                    }
                }
            }
            else
            {
                if (isPositionOccupied(boat.x, boat.y + boat.length, id))
                {
                    canMove = false;
                }
            }

            if (canMove)
            {
                boat.y += 1;
            }
            break;
        }
    }
}

void Boat::moveLeft(char id)
{
    for (auto &boat : boats)
    {
        if (boat.id == id && boat.x > 0)
        {
            bool canMove = true;
            if (boat.horizontal)
            {
                if (isPositionOccupied(boat.x - 1, boat.y, id))
                {
                    canMove = false;
                }
            }
            else
            {
                for (int i = 0; i < boat.length; ++i)
                {
                    if (isPositionOccupied(boat.x - 1, boat.y + i, id))
                    {
                        canMove = false;
                        break;
                    }
                }
            }

            if (canMove)
            {
                boat.x -= 1;
            }
            break;
        }
    }
}

void Boat::moveRight(char id)
{
    for (auto &boat : boats)
    {
        if (boat.id == id && (boat.x + boat.length - 1) < COLS - 1 && !gameOver)
        {
            bool canMove = true;
            if (boat.horizontal)
            {
                if (isPositionOccupied(boat.x + boat.length, boat.y, id))
                {
                    canMove = false;
                }
            }
            else
            {
                for (int i = 0; i < boat.length; ++i)
                {
                    if (isPositionOccupied(boat.x + 1, boat.y + i, id))
                    {
                        canMove = false;
                        break;
                    }
                }
            }

            if (canMove)
            {
                boat.x += 1;
            }
            break;
        }
        else if (boat.id == 's' && gameOver)
        {
            boat.x += 1;
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

bool Boat::isPositionOccupied(int x, int y, char id) const
{
    for (const auto &boat : boats)
    {
        if (boat.id != id)
        {
            if (boat.horizontal)
            {
                if (y == boat.y && x >= boat.x && x < boat.x + boat.length)
                {
                    return true;
                }
            }
            else
            {
                if (x == boat.x && y >= boat.y && y < boat.y + boat.length)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

