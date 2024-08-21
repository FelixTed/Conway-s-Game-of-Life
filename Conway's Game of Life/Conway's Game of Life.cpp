// Conway's Game of Life.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


//Any live cell with fewer than two live neighbours dies, as if by underpopulation.
//Any live cell with two or three live neighbours lives on to the next generation.
//Any live cell with more than three live neighbours dies, as if by overpopulation.
//Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <thread>

#include "Grid.h"
int main() {
    sf::RenderWindow window(sf::VideoMode(550, 500), "Conway's Game of Life", sf::Style::Close);
    sf::Event evnt;

    sf::RectangleShape playButton(sf::Vector2f(50.0f, 50.f));
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition(500.f, 450.f);

    // Create the vector of cubes and set the cubes inside
    std::vector<std::vector<sf::RectangleShape>> squares(10, std::vector<sf::RectangleShape>(10));
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            squares[i][j] = sf::RectangleShape(sf::Vector2f(49.0f, 49.0f));
            squares[i][j].setFillColor(sf::Color::White);
            squares[i][j].setOutlineColor(sf::Color::Black);
            squares[i][j].setPosition(i * 50.f, j * 50.f);
        }
    }

    Grid grid(squares);

    // Flag to check if the game is running
    std::thread gameThread;

    while (window.isOpen()) {
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
            case sf::Event::MouseButtonPressed:
                if (evnt.mouseButton.button == sf::Mouse::Left) {
                    // Get the position of the mouse click
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Calculate the grid position based on mouse position
                    int gridX = mousePos.x / 50;
                    int gridY = mousePos.y / 50;

                    // Ensure the click is within grid bounds
                    if (gridX >= 0 && gridX < 10 && gridY >= 0 && gridY < 10) {
                        // Toggle the color of the clicked square
                        if (squares[gridX][gridY].getFillColor() == sf::Color::White) {
                            squares[gridX][gridY].setFillColor(sf::Color::Black);
                            grid.setCell(gridY, gridX, 1);
                        }
                        else {
                            squares[gridX][gridY].setFillColor(sf::Color::White);
                            grid.setCell(gridY, gridX, 0);
                        }
                    }
                    else if (gridX == 10 && gridY == 9) {
                        if (playButton.getFillColor() == sf::Color::Green) {
                            playButton.setFillColor(sf::Color::Red);

                            // Start the game in a separate thread
                            gameThread = std::thread([&grid]() { grid.startGame(10); });
                        }
                        else {
                            playButton.setFillColor(sf::Color::Green);
                            grid.setStop(true);
                        }
                    }
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        window.clear();
        window.draw(playButton);
        for (int i = 0; i < squares.size(); ++i) {
            for (int j = 0; j < squares[i].size(); ++j) {
                window.draw(squares[i][j]);
            }
        }
        window.display();
    }

    // Wait for the game thread to finish if it's running
    if (gameThread.joinable()) {
        gameThread.join();
    }

    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
