//Our implementation of the Word Chain.
//Denjo163, Anthu456

//Includes the necessary libraries and files.
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;
const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

//Constructors for the functions.
void wordChain(const string &word1, const string &word2, const unordered_set<string> &dict);
void startMenu(string &word1, string &word2);
unordered_set<string> getDict();

//Starts the game.
int main() {
    string word1, word2;
    unordered_set<string> dict = getDict();
    startMenu(word1, word2);
    wordChain(word1, word2, dict);
    return 0;
}

//Prints out the start menu and choose the two words.
void startMenu(string &word1, string &word2) {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    cin >> word1 >> word2;
}

//Get all the words from teh given file dictionary.txt.
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

//Goes through all the neighbouring letters to find the next word.
vector<string> getNeighbors(const string &currentWord, const unordered_set<string> &dict, unordered_set<string> &usedWords) {
    vector<string> result;

    for (int i = 0; i < (int)currentWord.length(); i++) {
        for (int j = 0; j < (int)ALPHABET.length(); j++) {
            char newChar = ALPHABET[j];
            string neighbor = currentWord;
            neighbor[i] = newChar;         
            if (dict.count(neighbor) && !usedWords.count(neighbor)) {
                result.push_back(neighbor);
                usedWords.insert(neighbor);
            }
        }
    }
    return result;
}

//Finds the shortest path from the first to the second word by replacing one letter
//at the time and calling the getNeighbors function to find the next word.
void wordChain(const string &word1, const string &word2, const unordered_set<string> &dict) {
    queue<stack<string> > wordQueue;
    stack<string> tempStack;
    unordered_set<string> usedWords;
    stack<string> neighborPath;
    tempStack.push(word1);
    wordQueue.push(tempStack);

    while (!wordQueue.empty()) {
        neighborPath = wordQueue.front();
        wordQueue.pop();
        string currentWord = neighborPath.top();

        if (currentWord == word2) {
            cout << "The length of the shortest path is: " << neighborPath.size() - 1 << endl;
            cout << "Word ladder from " << word1 << " to " << word2 << ":\n";
            while (!neighborPath.empty()) {
                cout << neighborPath.top() << " ";
                neighborPath.pop();
            }
            cout << endl;
            return;
        } else {
            vector<string> neighbors = getNeighbors(neighborPath.top(), dict, usedWords);
            for (const string &neighbor : neighbors) {
                stack<string> copyStack = neighborPath;
                copyStack.push(neighbor);
                wordQueue.push(copyStack);
            }
        }
    }
    cout << "No word ladder found." << endl;
}
