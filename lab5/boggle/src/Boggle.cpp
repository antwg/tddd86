// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "grid.h"
#include "cube.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// TODO: implement the members you declared in Boggle.h
Boggle::Boggle() {
    board = Grid<Cube>(4,4);

    int i = 0;
    for(int row = 0; row < board.nRows; row++){
        for(int col = 0; col < board.nCols; col++){
            board[row][col] = Cube(CUBES[i]);
            i++;
        }
    }
}

void Boggle::loadDict(){
    this->dict = Lexicon(DICTIONARY_FILE);
}

bool Boggle::isInDict(const string& word){
    return dict.contains(word);
}

bool Boggle::searchForWord(const int x, const int y, const string& word){
    if(word == ""){
        return true;    // "" can always be found
    }

    for(int dy = -1; dy < 2; dy++){
        for(int dx = -1; dx < 2; dx++){
            if(board.inBounds(y + dy, x + dx) &&                                // The letter is in bounds,
                    !board.get(y + dy, x + dx).isVisited() &&                   // is not visited
                    board.get(y + dy, x + dx).getTopLetter()[0] == word[0]){    // and mathes the sought letter
                board.get(y + dy, x + dx).setVisited(true);
                bool found = searchForWord(x + dx, y + dy, word.substr(1));    // Search for the rest of the word
                board.get(y + dy, x + dx).setVisited(false);
                return found;
            }
        }
    }
    return false;   // Didn't find the next letter adjacent to (x, y)
}


bool Boggle::isWordInBoard(const string& word){
    for(int row = 0; row < board.nRows; row++){
        for(int col = 0; col < board.nCols; col++){
            if(searchForWord(col, row, word)){
                return true;
            }
        }
    }
    return false;
}

void Boggle::randomizeBoard(){
    for(int row = 0; row < board.nRows; row++){
        for(int col = 0; col < board.nCols; col++){
            board[row][col].shake();
        }
    }
    shuffle(board);
}

void Boggle::forceBoard(const string& boardString){
    int i = 0;
    for(int row = 0; row < board.nRows; row++){
        for(int col = 0; col < board.nCols; col++){
            board[row][col].forceTopLetter(boardString[i]);
            i++;
        }
    }
}

string Boggle::boardToString(){
    string output = "";

    for(int row = 0; row < board.nRows; row++){
        for(int col = 0; col < board.nCols; col++){
            output.append(board[row][col].getTopLetter());
        }
        output.append("\n");
    }
    return output;
}

void Boggle::addPlayerWord(const string& word){
    playerWords.insert(word);
}


set<string> Boggle::getPlayerWords(){
    return playerWords;
}

int Boggle::getScore(){
    return score;
}

void Boggle::addScore(int pts){
    score += pts;
}


void Boggle::doComputerTurn(){
    computerWords.clear();

    for(int y = 0; y < board.nRows; y++){
        for(int x = 0; x < board.nCols; x++){
            if(dict.containsPrefix(board.get(y, x).getTopLetter())){
                board.get(y, x).setVisited(true);
                search(x, y, board.get(y, x).getTopLetter());
                board.get(y, x).setVisited(false);
            }
        }
    }

    cout << "computer turn" << endl;
}

int Boggle::getComputerScore(){
    return computerScore;
}

void Boggle::search(const int x, const int y, string str){
    for(int dy = -1; dy < 2; dy++){
        for(int dx = -1; dx < 2; dx++){
            if(!(dx == 0 && dy == 0) &&
                    board.inBounds(y + dy, x + dx) &&                                // The letter is in bounds,
                    !board.get(y + dy, x + dx).isVisited()){    // and mathes the sought letter
                str.append(board.get(y + dy, x + dx).getTopLetter());

                cout << str << endl;

                if(str.length() > 3 && computerWords.count(str) < 1 && playerWords.count(str) < 1 && dict.contains(str)){
                    cout << "word" << endl;
                    computerWords.insert(str);
                    computerScore += str.length() - 3;
                }
                if(dict.containsPrefix(str)){
                    cout << "prefix" << endl;
                    board.get(y + dy, x + dx).setVisited(true);
                    search(x + dx, y + dy, str);    // Search for the rest of the word
                    board.get(y + dy, x + dx).setVisited(false);
                }

                str.pop_back();
            }
        }
    }
}

set<string> Boggle::getComputerWords(){
    return computerWords;
}
