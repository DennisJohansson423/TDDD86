//Our implementation of the "evil" hangman game.
//Denjo163, Anthu456

//Includes the necessary libraries and files.
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;
const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

//Constructors for the functions.
void hangMan(string &currentWord, unordered_set<string> &words, const int &maxGuesses, const string &wordsVisible);
unordered_set<string> getDict();
unordered_set<string> biggestFamily(char &guess, string &currentWord, unordered_set<string> &words);
void displayWords(const unordered_set<string> &words);
void playAgain();

//Starts the game and let the player choose the word length, maximun guesses and
//the visual of the remaining words. From those choices it finds all words within
//that lenght and starts the game woth those settings.
int main() {
    cout << "Welcome to Hangman." << endl;
    int wordLength = 0;
    int maxGuesses = 0;
    unordered_set<string> words = getDict();
    set<string> rightLengthWords;

    while (rightLengthWords.empty()) {
        cout << "Please type a word length: ";
        cin >> wordLength;
        for (const string &word: words) {
            int currentWordLength = word.length();
            if (currentWordLength == wordLength) {
                rightLengthWords.insert(word);
            }
        }
    }

    while(maxGuesses == 0) {
        cout << "Please enter maximum number of guesses: ";
        cin >> maxGuesses;
        }

    cout << "Do you want to see the remaining words? (y/n): " << endl;
    string wordsVisible;
    cin >> wordsVisible;

    for (auto it = words.begin(); it != words.end();) {
        if (it->size() != wordLength) {
            it = words.erase(it);
        } else {
            ++it;
        }
    }

    string currentWord = "";
    for (int i = 0; i < wordLength; i++) {
        currentWord.append("-");
    }
    hangMan(currentWord, words, maxGuesses, wordsVisible);
    return 0;
}

//Get all the words from the given file dictionary.txt.
unordered_set<string> getDict() {
    unordered_set<string> dict;
    ifstream file("dictionary.txt");
    string line;

    while (getline(file, line)) {
        dict.insert(line);
    }
    file.close();
    return dict;
}

// Finds the biggest family of choices from the current chosen letters.
unordered_set<string> biggestFamily(char &guess, string &currentWord, unordered_set<string> &words) {
    unordered_map<string, unordered_set<string>> families;

    for (string word : words) {
        string familyKey = currentWord; // Initialize with the current state of currentWord.
        for (int i = 0; i < word.size(); i++) {
            if (word[i] == guess) {
                familyKey[i] = guess; // Update the familyKey to include the guessed letter.
            }
        }
        families[familyKey].insert(word);
    }

    unordered_set<string> tempFamily;
    string tempKey;
    for (const auto &entry : families) {
        const string familyKey = entry.first;
        const unordered_set<string> family = entry.second;

        if (family.size() > tempFamily.size() || tempFamily.empty()) {
            tempFamily = family;
            tempKey = familyKey;
        }
    }

    // Update the currentWord with the new family key.
    currentWord = tempKey;

    return tempFamily;
}

//Called if the user wants to display the remaining words.
void displayWords(const unordered_set<string> &words) {
    cout << "Amount of words left: " << words.size() << endl;
}

//Called after the game is finished to see if the player wants to play again.
void playAgain() {
    string playAgain;
    cout << "Do you want to play again? (y/n): " << endl;
    cin >> playAgain;
    if (playAgain == "y") {
        system("clear");
        main();
    }
    else {
        cout << "Thanks for playing Hangman!" << endl;
        exit(1);
    }
}

//Lets the user choose the letter to guess the word and then checks if that letter is in the word by calling the
//biggestFamily function to find the biggest family of words, then returning tha new current word from the result
//of the biggest family and ask the user again, until the user wins or the guesses are out.
void hangMan(string &currentWord, unordered_set<string> &words, const int &maxGuesses, const string &wordsVisible) {
    unordered_set<char> guessed;
    int failedGuesses = 0;

    while (failedGuesses < maxGuesses) {

        if (!guessed.empty()) {
            cout << "Letters guessed: ";
            for (char guess : guessed) {
                cout << guess << ", ";
            }
            cout << endl;
        }

        cout << "Current word is: " << currentWord << endl;
        cout << "Guesses left: " << maxGuesses - failedGuesses << endl;
        cout << "Guess a letter: " << endl;

        string newLetter;
        while (newLetter.empty()) {
            char guess;
            cin >> guess;
            cout << endl;
            guess = tolower(guess);

            if (!guessed.count(guess) && ALPHABET.find(guess) != string::npos) {
                guessed.insert(guess);
                newLetter = guess;
                words = biggestFamily(guess, currentWord, words);
                if (wordsVisible == "y") {
                    displayWords(words);
                }

                if (currentWord.find('-') == string::npos) {
                    cout << "Congratulations, game won!" << endl;
                    cout << "The final word is: " << currentWord << endl;
                    playAgain();
                }
            } else {
                cout << "Please enter a valid letter that you haven't guessed before." << endl;
            }
        }
        failedGuesses++;
    }
    cout << "Out of guesses so you've lost." << endl;
    cout << "The word was: " << *words.begin() << endl;
    playAgain();

}


