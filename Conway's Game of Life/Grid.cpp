#include <iostream>

#include "Grid.h"
#include <thread>
#include <chrono>

int countLiveNeighbors(int row, int column, std::vector<std::vector<int>>& grid) {
    int count = 0;
    if (row > 0) {
        if (grid[row - 1][column] > 0)
            ++count;
        if (column > 0 && grid[row - 1][column - 1] > 0)
            ++count;
        if (column < grid[0].size() - 1 && grid[row - 1][column + 1] > 0)
            ++count;
    }
    if (column > 0 && grid[row][column - 1] > 0)
        ++count;
    if (column < grid[0].size() - 1 && grid[row][column + 1] > 0)
        ++count;
    if (row < grid.size() - 1) {
        if (grid[row + 1][column] > 0)
            ++count;
        if (column > 0 && grid[row + 1][column - 1] > 0)
            ++count;
        if (column < grid[0].size() - 1 && grid[row + 1][column + 1] > 0)
            ++count;
    }
    return count;
}


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

void Grid::startGame(int turns) {
    for (int i = 1; i <= turns; ++i) {
        system("CLS");
        std::cout << std::endl << "Turn: " << i << std::endl;
        printGrid();

        std::vector<std::vector<int>> tempVec(grid.size(), std::vector<int>(grid[0].size(), 0));

        for (int j = 0; j < grid.size(); j++) {
            for (int z = 0; z < grid.size(); z++) {
                int neighbors = countLiveNeighbors(j, z, grid);
                if (grid[j][z] > 0 && neighbors < 2)
                    tempVec[j][z] = 0;
                else if (grid[j][z] > 0 && neighbors > 3)
                    tempVec[j][z] = 0;
                else if (grid[j][z] > 0 && (neighbors == 2 || neighbors == 3))
                    tempVec[j][z] = 1;
                else if (grid[j][z] <= 0 && neighbors == 3)
                    tempVec[j][z] = 1;
            }
        }
        grid = tempVec;

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}