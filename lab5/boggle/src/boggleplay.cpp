// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
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

    string input;
    set<string> playerWords;
    int score = 0;
    while (true){
        cout << "\nType a word (or press Enter to end your turn): " << endl;
        getline(cin, input);

        clearConsole();

        if (input.empty()){
            cout << "It's my turn!" << endl;
            boggle.doComputerTurn();
            return;
        }

        if (input.size() < 4) {
            cout << "Word too short (minimum 4 letters)!" << endl;
        } else if (playerWords.count(input) > 0) {
            cout << "You have already guessed this word!" << endl;
        //} else if (!boggle.isInDict(input)){
        //    cout << "Word is not in the dictionary!" << endl;
        } else {
            playerWords.insert(input);
            score += input.size() - 3;
            cout << "You found a new word! \"" << input << "\"\n...\n" << endl;

            // Print word list
            cout << "Your words (" << playerWords.size() << "): " << endl;
            for (string word : playerWords){
                cout << "\"" << word << "\"" << endl;
            }
            //cout << endl;

            // Print score
            cout << "Your score: " << score << endl;


        }



    }

    //For debugging
    cout << boggle.boardToString() << endl;
}

bool onlyLetters(string str){
    for (unsigned int i = 0; i < str.size(); i++){
        if (!isalpha(str[i])){
            return false;
        }
    }
    return true;
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
