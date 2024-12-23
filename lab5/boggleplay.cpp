#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include "Boggle.cpp"


/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    clearConsole();
    boggle.inputWords();

}


void Boggle::inputWords() {
    string boardBuild = "";
    string emptyWord = "-";
    string guessedWord;
    int minWordLength = 4;
    int playerScore = 0;
    int computerScore = 0;
    Grid<char> currentBoard(4, 4);
    unordered_set<string> guessedWords;
    drawBoard(boardBuild);
    while (guessedWord.empty()) {
        cout << "Type a word with min lneght 4 (or type '-' to end your turn): " << endl;
        cin >> guessedWord;
        clearConsole();
        for (const string &word: guessedWords) {
            string newGuessedWord;
            for (char &ch : guessedWord) {
                  newGuessedWord += toupper(ch);
              }
            if (word == newGuessedWord) {
                cout << "Word has already been guessed! " << endl;
                guessedWord.clear();
            }
        }
        if (guessedWord == emptyWord) {
            cout << "It's my turn! " << endl;
            unordered_set<string> wordList;
            wordList = computerSearch(boardBuild);
            for (string word : wordList) {
                for (string word2 : guessedWords) {
                    if (word == word2) {
                        wordList.erase(word);
                    }
                }
            }
            cout << "My words " << "(" << wordList.size() << "): ";
            cout << "{";
            auto it = wordList.begin();
            for (string word: wordList) {
                if (++it == wordList.end()) {
                    cout << '"' << word << '"';
                } else {
                cout << '"' << word << '"' << ", ";
                }
            }
            cout << "}" << endl;
            for (string word:wordList) {
                computerScore += word.length() - 3;
            }
            if (computerScore > playerScore) {
            cout << "My score: " << computerScore << endl;
            cout << "Ha ha ha, I destroyed you. Better luck next time, puny human! " << endl;
            cout << endl;
            } else if (computerScore == playerScore) {
                cout << "It's a draw!" << endl;
            } else if(computerScore < playerScore) {
                cout << "WOW, you defeated me! Congratulations!" << endl;
            }
       } else {
            if(playerSearch(guessedWord, boardBuild) == true && guessedWord.size() >= minWordLength) {
                  string fixedGuessedWord;
                  for (char &ch : guessedWord) {
                        fixedGuessedWord += toupper(ch);
                    }
                  printCurrentBoard(boardBuild);
                  cout << "You found a new word! " << '"' << fixedGuessedWord << '"' << endl;
                  cout << endl;
                  if (fixedGuessedWord.size() == 4) {
                      playerScore += 1;
                  } else {
                      playerScore += fixedGuessedWord.size() - 3;
                  }
                  guessedWords.insert(fixedGuessedWord);
                  cout << "Your words (" << guessedWords.size() << "): ";
                  cout << "{";
                  auto it = guessedWords.begin();
                  for (string word:guessedWords) {
                      if (++it == guessedWords.end()) {
                          cout << '"' << word << '"';
                      } else {
                      cout << '"' << word << '"' << ", ";
                      }
                  }
                  cout << "}" << endl;
                  cout << "Your score: " << playerScore << endl;
                  guessedWord.clear();
            } else {
                  clearConsole();
                  cout << "Word couldn't be created, false guess! " << endl;
                  printCurrentBoard(boardBuild);
                  guessedWord.clear();
            }
        }
    }
}


void Boggle::drawBoard(string &boardBuild) {
    Grid<char> grid(4, 4);
    string newBoard;
    cout << "Do you want to generate a random board? (y/n)" << endl;
    cin >> newBoard;
    clearConsole();
    if (newBoard == "y") {
        for (int i = 0; i < grid.numRows(); i++) {
            for (int j = 0; j < grid.numCols(); j++) {
                int cubeIndex = i * grid.numCols() + j;
                int sideIndex = randomInteger(0, CUBE_SIDES - 1);
                grid[i][j] = CUBES[cubeIndex][sideIndex];
                cout << grid[i][j];
                boardBuild += grid[i][j];
            }
            cout << endl;
        }
    } else if (newBoard == "n") {
        string custom;
        string fixedCustom;
        bool inAlphabet = false;
        while (custom.length() != 16 && inAlphabet == false) {
            cout << "OBS! Enter an exactly 16 letter long string (A-Z) to create a custom board: " << endl;
            cin >> custom;
            string fixedGuessedWord;
            for (char &ch : custom) {
                  fixedCustom += toupper(ch);
              }
            clearConsole();
            for (char letter : fixedCustom) {
                if (isalpha(letter)) {
                    inAlphabet == true;
                }
            }
        }
        boardBuild = fixedCustom;
        int index = 0;
        for (int i = 0; i < grid.numRows(); i++) {
            for (int j = 0; j < grid.numCols(); j++) {
                grid[i][j] = fixedCustom[index++];
                cout << grid[i][j];
            }
            cout << endl;
        }
    }
}


/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
