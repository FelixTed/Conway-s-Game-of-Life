#include <iostream>

#include "Grid.h"
#include <thread>
#include <chrono>

int countLiveNeighbors(int row, int column, std::vector<std::vector<int>>& grid) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    // Iterate over the 3x3 neighborhood centered around (row, column)
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            // Skip the center cell itself
            if (i == 0 && j == 0) continue;

            int newRow = row + i;
            int newCol = column + j;

            // Check if the neighbor is within the grid boundaries
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                if (grid[newRow][newCol] > 0) {
                    ++count;
                }
            }
        }
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
        if (stop)
            exit(0);
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
       

        std::vector<std::vector<int>> tempVec(grid.size(), std::vector<int>(grid[0].size(), 0));

        for (int j = 0; j < grid.size(); j++) {
            for (int z = 0; z < grid.size(); z++) {
                int neighbors = countLiveNeighbors(j, z, grid);
                if (grid[j][z] > 0 && neighbors < 2) {
                    tempVec[j][z] = 0;
                    squares[z][j].setFillColor(sf::Color::White);
                }
                else if (grid[j][z] > 0 && neighbors > 3) {
                    tempVec[j][z] = 0;
                    squares[z][j].setFillColor(sf::Color::White);
                }
                else if (grid[j][z] > 0 && (neighbors == 2 || neighbors == 3)) {
                    tempVec[j][z] = 1;
                   squares[z][j].setFillColor(sf::Color::Black);
                }
                else if (grid[j][z] <= 0 && neighbors == 3) {
                    tempVec[j][z] = 1;
                    squares[z][j].setFillColor(sf::Color::Black);
                }
            }

        }
        grid = tempVec;


  
    }
}