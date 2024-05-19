
#include <iostream>
#include "Boat.hpp"
using namespace std;



vector<vector<int>> boatList(8, vector<int>(8, false));


Boat::Boat() : boatList(ROWS, vector<int>(COLS, 0)), BoatRow(1), BoatCol(2)
{
    boatList[BoatRow][BoatCol] = 1;
}

Boat::~Boat()
{
}

void Boat::grid()
{

    boatList[BoatRow][BoatCol] = true;
    // cout << "Boat is at position: (" << BoatRow << ", " << BoatCol << ")" << endl;

    for (int i = 0; i < ROWS; ++i)
    {
        cout << endl; 
        for (int j = 0; j < COLS; ++j)
        {
        cout << (boatList[i][j] ? "0 " : "1 ");
        }
        cout << endl;
    }
}


int Boat:: moveU()
{

    if (checkNeighbour(BoatRow, BoatCol, 1, 'U'))
    {
        boatList[BoatRow][BoatCol] = false;
        boatList[BoatRow-1][BoatCol] = true;
        return 1;
    }
    else {
        cout << "It's impossible to move the boat to the top." << endl;
        
    }
    return 0 ;
}

int Boat:: moveD()
{

    if (checkNeighbour(BoatRow, BoatCol, 1, 'D'))
    {
        boatList[BoatRow][BoatCol] = false;
        boatList[BoatRow+1][BoatCol] = true;
        return 1;
    }
    else {
        cout << "It's impossible to move the boat to the bottom" << endl;

    }
    return 0;
}

int Boat:: moveL()
{

    if (checkNeighbour(BoatRow, BoatCol, 1, 'L'))
    {
        boatList[BoatRow][BoatCol] = false;
        boatList[BoatRow][BoatCol-1] = true;
        return 1;
    }
    else {
    cout << "It's impossible to move the boat to the left." << endl;
    }
    return 0;
}

int Boat:: moveR()
{

    if (checkNeighbour(BoatRow, BoatCol, 1, 3))
    {
        boatList[BoatRow][BoatCol] = false;
        boatList[BoatRow][BoatCol+1] = true;
        return 1;
    }
     else
    {
    cout << "It's impossible to move the boat to the right." << endl;
    }

    return 0;
     
}


bool Boat::checkNeighbour(int row, int col, int distance, char direction)
{
    if (direction == 'H')
    {
        return row - distance >= 0 && !boatList[row - distance][col];
    }
    else if (direction == 'B')
    {
        return row + distance < ROWS && !boatList[row + distance][col];
    }
    else if (direction == 'G')
    {
        return col - distance >= 0 && !boatList[row][col - distance];
    }
    else if (direction == 'D')
    {
        return col + distance < COLS && !boatList[row][col + distance];
    }

    return false;
}