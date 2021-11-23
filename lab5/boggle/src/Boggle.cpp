/*
 * antwe841
 * bensu844
 *
 * This class handles the logic for the boggle game. It has functions to manipulate the board,
 * search for words and handle scores. It contains the computers turns logic as well.
 */

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "grid.h"
#include "cube.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
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

void Boggle::resetGame(){
    loadDict();

    score = 0;
    computerScore = 0;

    playerWords.clear();
    computerWords.clear();

}

bool Boggle::isInDict(const string& word){
    return dict.contains(word);
}

bool Boggle::searchForWord(const int x, const int y, const string& word){
    if(word == ""){
        return true;    // "" can always be found
    }

    board[y][x].setVisited(true);
    for(int dy = -1; dy < 2; dy++){
        for(int dx = -1; dx < 2; dx++){
            if(board.inBounds(y + dy, x + dx) &&                                // The letter is in bounds,
                    !board.get(y + dy, x + dx).isVisited() &&                   // is not visited
                    board.get(y + dy, x + dx).getTopLetter()[0] == word[0] &&   // and matches the sought letter
                    searchForWord(x + dx, y + dy, word.substr(1))){
                board[y][x].setVisited(false);
                return true;
            }
        }
    }
    board[y][x].setVisited(false);
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
    for(int y = 0; y < board.nRows; y++){
        for(int x = 0; x < board.nCols; x++){
            if(dict.containsPrefix(board.get(y, x).getTopLetter())){ // Continue if prefix, else try next cube
                // Exhaustive search starting at current cube
                search(x, y, board.get(y, x).getTopLetter());
            }
        }
    }

    cout << "computer turn" << endl;
}

int Boggle::getComputerScore(){
    return computerScore;
}

void Boggle::search(const int x, const int y, string str){
    // For each cube around current cube
    board[y][x].setVisited(true);
    for(int dy = -1; dy < 2; dy++){
        for(int dx = -1; dx < 2; dx++){
            if(board.inBounds(y + dy, x + dx) &&                                // The letter is in bounds,
                    !board.get(y + dy, x + dx).isVisited()){                    // hasn't already been visited
                str.append(board[y + dy][x + dx].getTopLetter());           // Save cube/top letter

                // If valid word
                if(str.length() > 3 && computerWords.count(str) < 1 && playerWords.count(str) < 1 && dict.contains(str)){
                    computerWords.insert(str);
                    computerScore += str.length() - 3;
                }
                // If valid prefix
                if(dict.containsPrefix(str)){
                    search(x + dx, y + dy, str);    // Search for the rest of the word
                }
                // Backtrack
                str.pop_back();
            }
        }
    }
    board[y][x].setVisited(false);
}

set<string> Boggle::getComputerWords(){
    return computerWords;
}
