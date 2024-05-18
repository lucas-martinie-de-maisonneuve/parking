
#include <iostream>
#include "Boat.hpp"
using namespace std;


Boat::Boat(char id, int x, int y, int length, bool orientation)
    : id(id), x(x), y(y), length(length), orientation(orientation) {

    }


Boat::~Boat() {

}

void Boat::grid()
{
    const int ROWS = 8, COLS = 8;
    int squareSize = 50;

    for (int i = 0; i < ROWS; ++i)
    {
            cout <<endl<<"i" << endl;
        for (int j = 0; j < COLS; ++j)
        {
        cout << "0";

          
        }
    }
}
