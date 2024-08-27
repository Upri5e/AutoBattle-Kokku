#pragma once
#include <Vector>
#include "Types.h"
#include <memory>
class Grid
{

public:

    Grid(int Lines, int Columns);
    ~Grid();

    std::vector<std::shared_ptr<Types::GridBox>> grids;

    int xLenght;
    int yLength;
    
    // prints the matrix that indicates the tiles of the battlefield
    void drawBattlefield();
};

