/*
 * antwe841
 * bensu844
 *
 * This file acts as an interface between the player and the ongoing boggle game.
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"

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
        answer = trim(toUpperCase(answer));
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
    boggle.resetGame();

    if (!yesOrNo("Do you want to generate a random board? (Y/N) ")){
        boggle.forceBoard(promptBoardString());
    } else {
        boggle.randomizeBoard();
    }

    string input;

    cout << "It's your turn!" << endl;
    while (true){

        cout << "\n==================================\n" << endl;
        cout << boggle.boardToString() << endl;;

        cout << "Type a word (or press Enter to end your turn): " << endl;
        getline(cin, input);

        if (input.empty()){
            cout << "It's my turn!" << endl;
            boggle.doComputerTurn();
            cout << "My words (" << boggle.getComputerWords().size() << "): " << endl;
            for (string word : boggle.getComputerWords()){
                cout << "\"" << word << "\"" << endl;
            }

            // Print score
            cout << "My score: " << boggle.getComputerScore() << endl;

            if(boggle.getComputerScore() > boggle.getScore()){
                cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
            } else {
                cout << "Congratulations on clearly cheating. You win..." << endl;
            }
            return;
        }

        for (auto & c: input) c = toupper(c);

        if (input.size() < 4) {
            cout << "Word too short (minimum 4 letters)!" << endl;
        } else if (boggle.getPlayerWords().count(input) > 0) {
            cout << "You have already guessed this word!" << endl;
        } else if (!boggle.isInDict(input)){
            cout << "Word \"" << input <<"\" is not in the dictionary!" << endl;
        } else if (!boggle.isWordInBoard(input)) {
            cout << "Word \"" << input <<"\" does not exist in the board!" << endl;
        } else {
            boggle.addPlayerWord(input);
            boggle.addScore(input.size() - 3);
            cout << "You found a new word! \"" << input << "\"\n...\n" << endl;

            // Print word list
            cout << "Your words (" << boggle.getPlayerWords().size() << "): " << endl;
            for (string word : boggle.getPlayerWords()){
                cout << "\"" << word << "\"" << endl;
            }

            // Print score
            cout << "Your score: " << boggle.getScore()<< "\"" << endl;
        }
    }
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
