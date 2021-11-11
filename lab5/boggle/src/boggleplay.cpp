// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need

bool onlyLetters(const string& str){
    for (unsigned int i = 0; i < str.size(); i++){
        if(!isalpha(str[i])){
            return false;
        }
    }
    return true;
}

string promptBoardString(){
    cout << "Enter 16 letters: " << endl;
    while (true) {
        string answer;
        getline(cin, answer);
        answer = trim(toLowerCase(answer));
        if (answer.size() == 16 && onlyLetters(answer)) {
            return answer;
        } else {
            cout << "Invalid input. Please enter 16 letters (A-Z. a-z): " << endl;
        }
    }
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)

    if (!yesOrNo("Do you want to generate a random board? (Y/N) ")){
        boggle.forceBoard(promptBoardString());
    } else {
        boggle.randomizeBoard();
    }

    cout << boggle.boardToString() << endl;
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
