#ifndef GUARD_GRID_H
#define GUARD_GRID_H

#include <vector>
#include <SFML/Graphics.hpp>

class Grid {
public:
    // Constructor: filling the array with 0s and initializing the reference
    Grid(std::vector<std::vector<sf::RectangleShape>>& s)
        : grid(10, std::vector<int>(10, 0)), squares(s) { }

    // Select a cell by row and column and set it to desired int value
    void setCell(int row, int column, int value);

    // Returns the value of the specified cell
    int getCell(int row, int column);

    // Prints the whole grid to the console
    void printGrid();

    // Plays the game for the specified amount of time
    void startGame(int turns);

    // Returns a copy of the grid
    std::vector<std::vector<int>> getGrid() { return grid; }

    void setStop(bool s) { stop = s; }
    
    bool getStop() { return stop; }

private:
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<sf::RectangleShape>>& squares;  // Reference to the squares vector

    bool stop = false;
};

#endif // GUARD_GRID_H
