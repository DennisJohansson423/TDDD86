#include <sstream>
#include <fstream>
#include <iostream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "unordered_set"
#include "lexicon.h"
#include "bogglemain.h"
#include <cctype>

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};


void Boggle::printCurrentBoard(string& boardBuild) {
    Grid<char> grid(4, 4);
    int index = 0;
    for (int i = 0; i < grid.numRows(); i++) {
        for (int j = 0; j < grid.numCols(); j++) {
            grid[i][j] = boardBuild[index++];
            cout << grid[i][j];
        }
        cout << endl;
    }
}


bool Boggle::playerSearch(const string &guessedWord, const string &boardBuild) {
    int index = 0;
    int row, column;
    Grid<char> grid(4, 4);
    string fixedGuessedWord;
    for (const char &ch : guessedWord) {
            fixedGuessedWord += toupper(ch);
        }
    for (int i = 0; i < grid.numRows(); i++) {
        for (int j = 0; j < grid.numCols(); j++) {
            grid[i][j] = boardBuild[index++];
        }
    }
    for (int i = 0; i < grid.numRows(); i++) {
        for (int j = 0; j < grid.numCols(); j++) {
            if (grid[i][j] == fixedGuessedWord[0]) {
                row = i;
                column = j;
                string newWord = fixedGuessedWord.substr(1);
                string visited;
                visited += grid[row][column];
                if(findGivenNeighbours(grid, row, column, fixedGuessedWord, newWord, visited)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Boggle::findGivenNeighbours(const Grid<char> &grid, const int &row, const int &column, const string &guessedWord, const string &newWord, string &visited) {
    if (lexicon->contains(visited) && visited == guessedWord) {
        return true;
    } else {
        for (int i = row - 1; i <= row + 1; ++i) {
            for (int j = column - 1; j <= column + 1; ++j) {
                if (grid.inBounds(i, j)) {
                    if (i != row || j != column) {
                        if (grid[i][j] == newWord[0]) {
                            int newRow = i;
                            int newColumn = j;
                            visited += grid[i][j];
                            if (findGivenNeighbours(grid,newRow, newColumn, guessedWord, newWord.substr(1), visited)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
}


const unordered_set<string> Boggle::computerSearch(const string &boardBuild) {
    Grid<char> grid(4, 4);
    unordered_set<string> allWords;
    int index = 0;
    for (int i = 0; i < grid.numRows(); i++) {
        for (int j = 0; j < grid.numCols(); j++) {
            grid[i][j] = boardBuild[index++];
        }
    }
    for (int i = 0; i < grid.numRows(); i++) {
        for (int j = 0; j < grid.numCols(); j++) {
            string currentWord = string(1, grid[i][j]);
            unordered_set<int> visited;
            visited.insert(i * grid.numCols() + j);
            findAllWords(currentWord, i, j, allWords, grid, visited);
        }
    }
    return allWords;
}

void Boggle::findAllWords(const string &chosen, int row, int col, unordered_set<string> &allWords, Grid<char> &grid, unordered_set<int> &visited) {
    if (lexicon->contains(chosen) && chosen.length() >= MIN_WORD_LENGTH) {
        allWords.insert(chosen);
    }
    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j) {
            int pos = i * grid.numCols() + j;
            if (grid.inBounds(i, j) && visited.find(pos) == visited.end() && lexicon->containsPrefix(chosen + grid[i][j])) {
                visited.insert(pos);
                findAllWords(chosen + grid[i][j], i, j, allWords, grid, visited);
                visited.erase(pos);
            }
        }
    }
}
