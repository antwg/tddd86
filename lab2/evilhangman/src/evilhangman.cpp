#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/*
 * Opens the dictionary.txt file and loads all words into an unordered set.
 */
void getDict(unordered_set<string>& dict){
    ifstream file("dictionary.txt");
    string line;
    while (getline(file, line)){
        dict.insert(line);
    }
    file.close();
}

int getNumberOfGuesses(){
    cout << "Enter number of guesses:" << endl;

    // add functionality
}

bool getShowRemainingWords(){
    cout << "Do you want to see the number of remaining words?" << endl;

   // add functionality
}

int main() {
    int remainingGuesses;
    //int remainingWords;
    bool showRemainingWords;
    string wordProgress;
    string guessedLetters = "";
    unordered_set<string> possibleWords = {};

    cout << "Welcome to Hangman." << endl;


    // TODO: Finish the program!
    // 1. read file
    unordered_set<string> dict;
    getDict(dict);

    // 2. prompt word length

    // 3. prompt number of guesses
    remainingGuesses = getNumberOfGuesses();

    // 4. prompt show number of words
    showRemainingWords = getShowRemainingWords();

    // 5. Actual game

    // a. create list of words based on length
    // DONE IN 2.

    // b. print remaining guesses + guessed letters (+ remaining words)
    cout << "You have " << remainingGuesses << " guesses left." << endl;
    cout << "Guessed letters: " << guessedLetters << endl;
    cout << wordProgress << endl;
    if (showRemainingWords) {
        cout << "Remaining words: " << possibleWords.size() << endl;
    }

    // c. prompt guess

    // d. partition words based on family

    // e. find largest family, ...

    // f. reveal word if out of guesses

    // g. congrats

    // 6. play again?
    return 0;
}
