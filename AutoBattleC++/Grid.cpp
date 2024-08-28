#include "Grid.h"
#include "Types.h"
#include <memory>

Grid::Grid(int Lines, int Columns) : xLength(Columns), yLength(Lines) //Fixed the reversed column and rows issue
{
	//Console.WriteLine("The battle field has been created\n");
	for (int j = 0; j < yLength; j++) //Col
	{
		for (int i = 0; i < xLength; i++) //Row
		{
			int index = j * xLength + i;
			grids.emplace_back(std::make_shared<Types::GridBox>(i, j, false, index)); // use emplace_back to append the new element
			printf("Created Box %d at X=%d, Y=%d\n",index, i, j);
			//Console.Write($"{newBox.Index}\n");
		}
	}
	//drawBattlefield(Lines, Columns);
}

Grid::~Grid()
{

}

void Grid::drawBattlefield()
{
	for (int j = 0; j < yLength; j++) //Col
	{
		for (int i = 0; i < xLength; i++) //Row
		{
			//Loop through the grids and assign icon based on occupation status
			std::shared_ptr<Types::GridBox> currentgrid = grids[GetBoxIndexByLocation(i,j)];
			printf("[%s]\t", currentgrid->icon.c_str());
		}
		printf("\n");
	}
	printf("\n");
}

//Gets the box index inside grids
int Grid::GetBoxIndexByLocation(int x, int y)
{
	if (x < 0 || x >= xLength || y < 0 || y >= yLength)
	{
		printf("Box location invalid. Enter locations between 0 and grid width and height... %d X %d", xLength, yLength);
		return -1;
	}
	return y * xLength + x;
}
