/*
 * antwe841
 * bensu844
 *
 * This file declares the functions for Boggle.cpp. It also stores some variables
 * such as the dictionary, the board and scores.
 */

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <set>
#include "grid.h"
#include "cube.h"
#include "lexicon.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    Lexicon dict;

    Boggle();

    /*
     * Loads the dictionary from a file.
     */
    void loadDict();

    /*
     * Resets the game.
     */
    void resetGame();

    /*
     * Returns true if the given word exists in the dictionary, otherwise false.
     */
    bool isInDict(const string& word);

    /*
     * Recursively searches the board around the coordinates (x, y) for the given word.
     * Returns true if the word was found, otherwise false.
     */
    bool searchForWord(const int x, const int y, const string& word);

    /*
     * Searches the board for the given word. Returns true if the
     * given word exists somewhere in the board, otherwise false.
     */
    bool isWordInBoard(const string& word);

    /*
     * Randomizes the board
     */
    void randomizeBoard();

    /*
     * Forces the board configuration. Assumes that the given string is valid.
     */
    void forceBoard(const string& boardString);

    /*
     * Returns a string representing the board state.
     */
    string boardToString();

    /*
     * Adds a word to the set of words found by the player.
     */
    void addPlayerWord(const string& word);

    /*
     * Returns a set of strings containing the words found by the player.
     */
    set<string> getPlayerWords();

    /*
     * Returns the player's score.
     */
    int getScore();

    /*
     * Incrments the player's score by a given number.
     */
    void addScore(int pts);

    /*
     * Executes the computer's turn. Finds all the words that the player didn't find
     * and adds them to the set of words found by the computer.
     */
    void doComputerTurn();

    /*
     * Returns the computer's score.
     */
    int getComputerScore();

    /*
     * Recursively searches the board around the given coordinates for words starting with the
     * letters in str and adds them to computerWords.
     */
    void search(const int x, const int y, string str);

    /*
     * Returns the set of words found by the computer.
     */
    set<string> getComputerWords();

private:
    set<string> playerWords;
    int score = 0;

    Grid<Cube> board;
    int computerScore = 0;
    set<string> computerWords;
};

#endif
