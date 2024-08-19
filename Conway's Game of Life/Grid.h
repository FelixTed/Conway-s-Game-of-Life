#ifndef GUARD_GRID_H
#define GUARD_GRID_H
#include <vector>

//A positive value (>0) means a live cell
//A value of 0 or less means a dead cell

class Grid {
public:
	//filling the array with 0s
	Grid() : grid(10, std::vector<int>(10, 0)) { }

	//Select a cell by row and column and set it to desired int value
	void setCell(int row, int column, int value);

	//Returns the value of the specified cell
	int getCell(int row, int column);

	//Prints the whole grid to the console
	void printGrid();
private:
	std::vector<std::vector<int>> grid;
};

#endif GUARD_GRID_H
