//Our implementation of the life game.

//Includes the necessary libraries and files.
#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>

using namespace std;

//Contructors for the functions.
void startMenu(Grid<char> &grid);
void choice(Grid<char> &grid);
void printGrid(const Grid<char> &GRID);
void animate(Grid<char> &grid, const int ROWS, const int COLUMNS);
int findNeighbourNumber(const Grid<char> &GRID, int row, int column);

//Starts the game.
int main(){
    Grid<char> grid(0, 0);

    startMenu(grid);
    printGrid(grid);
    choice(grid);

    cout << "Have a nice Life! " << endl;
    return 0;
}


//Prints out the start menu and sets the grid.
void startMenu(Grid<char> &grid){
    string fileName;
    ifstream file;
    int rows;
    int columns;

    const string STARTTEXT =
        "Welcome to the TDDD86 Game of Life,\n"
        "a simulation of the lifecycle of a bacteria colony.\n"
        "Cells (X) live and die by the following rules:\n"
        " - A cell with 1 or fewer neighbours dies.\n"
        " - Locations with 2 neighbours remain stable.\n"
        " - Locations with 3 neighbours will create life.\n"
        " - A cell with 4 or more neighbours dies.\n";

    cout << STARTTEXT;
    cout << "Grid input file name? ";
    cin >> fileName;
    file.open(fileName);

    file >> rows >> columns;
    grid.resize(rows, columns);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            file >> grid[i][j];
        }
    }
    file.close();
}


//Prints the current state of the grid.
void printGrid(const Grid<char> &GRID){
    for (int i = 0; i < GRID.numRows(); i++){
        for (int j = 0; j < GRID.numCols(); j++){
            cout << GRID[i][j];
        }
        cout << endl;
    }
}


//Gives you three choices to do, a)nimate, t)ick, q)uit.
void choice(Grid<char> &grid){
    char input;
    while (true){
        cout << "a)nimate, t)ick, q)uit?";
        cin >> input;
        if (input == 'a'){
            while (true){
            clearConsole();
            animate(grid, grid.numRows(), grid.numCols());
            pause(100);
            }
        } else if(input == 't'){
            clearConsole();
            animate(grid, grid.numRows(), grid.numCols());
        } else if (input == 'q'){
            return;
        }
    }
}


//Animates the game according to the given demands and calls the
//neighbours function to check the demands.
void animate(Grid<char> &grid, const int ROWS, const int COLUMNS){
        Grid<char> tempGrid = grid;
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++){
                if (findNeighbourNumber(grid, i, j) <= 1 || findNeighbourNumber(grid, i, j) >= 4){
                    tempGrid.set(i, j, '-');
                }
                else if (findNeighbourNumber(grid, i, j) == 3){
                    tempGrid.set(i, j, 'X');
                }
            }
        }
        grid = tempGrid;
        printGrid(grid);
    }


//Finds the amount of neighbours for each position in the grid.
int findNeighbourNumber(const Grid<char> &GRID, const int ROW, const int COLUMN){
    int neighbours = 0;
    for (int i = ROW - 1; i <= ROW + 1; ++i){
        for (int j = COLUMN - 1; j <= COLUMN + 1; ++j){
            if (GRID.inBounds(i, j)){
                if (i != ROW || j != COLUMN){
                    if (GRID[i][j] == 'X'){
                        neighbours++;
                    }
                }
            }
        }
    }
    return neighbours;
}

