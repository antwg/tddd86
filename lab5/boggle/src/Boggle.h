// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "grid.h"
#include "cube.h"
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    Boggle();

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

private:
    // TODO: decide the private member variables/functions and declare them
    Grid<Cube> board;
};

#endif
