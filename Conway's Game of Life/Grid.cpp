#include <iostream>

#include "Grid.h"

//Setting the selected cell to desired value
void Grid::setCell(int row, int column, int value) {

	grid[row][column] = value;
}

int Grid::getCell(int row, int column) {
	return grid[row][column];
}

void Grid::printGrid() {
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}