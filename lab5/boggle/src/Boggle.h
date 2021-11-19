// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <set>
#include "grid.h"
#include "cube.h"
#include "lexicon.h"
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    Lexicon dict;

    Boggle();

    /*
     *
     */
    void loadDict();

    /*
     *
     */
    bool isInDict(const string& word);

    bool searchForWord(const int x, const int y, const string& word);

    bool isWordInBoard(const string& word);

    // TODO: decide the public member functions and declare them
    /*
     *
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

    void addPlayerWord(const string& word);

    set<string> getPlayerWords();

    int getScore();

    void addScore(int pts);

    void doComputerTurn();

    int getComputerScore();

    void search(const int x, const int y, string str);

    set<string> getComputerWords();

private:
    // TODO: decide the private member variables/functions and declare them
    set<string> playerWords;
    int score = 0;


    Grid<Cube> board;
    int computerScore = 0;
    set<string> computerWords;
};

#endif
