#include "Grid.h"
#include "Types.h"
#include <memory>

Grid::Grid(int Lines, int Columns)
{
    xLenght = Lines;
    yLength = Columns;
    //Console.WriteLine("The battle field has been created\n");
    for (int i = 0; i < Lines; i++)
    {

        for (int j = 0; j < Columns; j++)
        {
            auto newBox = std::make_shared<Types::GridBox>(i, j, false, (Columns * i + j)); //Change to a unique ptr to avoid memory leak 
            grids.push_back(std::move(newBox)); // use emplace_back to append the new element
            //Console.Write($"{newBox.Index}\n");
        }
    }
	//drawBattlefield(Lines, Columns);
}

Grid::~Grid() 
{

}

void Grid::drawBattlefield(int Lines, int Columns)
{
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            //Fix This
            Types::GridBox* currentgrid = new Types::GridBox(0, 0, false, 0);
            if (currentgrid->ocupied)
            {
                //if()
                printf("[X]\t");
            }
            else
            {
                printf("[ ]\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}