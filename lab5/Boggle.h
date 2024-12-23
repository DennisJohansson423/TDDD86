#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "lexicon.h"
#include "grid.h"

using namespace std;


class Boggle {
public:
    const string DICTIONARY_FILE= "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    const unordered_map<int, string> BOARD;
    const Lexicon* lexicon = new Lexicon(DICTIONARY_FILE);


    void drawBoard(string &boardBuild);
    void inputWords();
    bool playerSearch(const string &guessedWord, const string &boardBuild);
    const unordered_set<string> computerSearch(const string &boardBuild);
    bool findGivenNeighbours(const Grid<char> &grid, const int &row, const int &column, const string &guessedWord, const string &newWord, string &visited);
    void printCurrentBoard(string &boardBuild);
    void findAllWords(const string &chosen, int row, int col, unordered_set<string> &allWords, Grid<char> &grid, unordered_set<int> &visited);


private:

};

#endif
