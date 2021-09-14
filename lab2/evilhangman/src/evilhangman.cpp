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

int main() {
    cout << "Welcome to Hangman." << endl;
    unordered_set<string> dict;
    getDict(dict);
    // TODO: Finish the program!
    // 1. read file

    // 2. prompt word length

    // 3. prompt number of guesses

    // 4. prompt show number of words

    // 5. Actual game

    // a. create list of words based on length

    // b. print remaining guesses + guessed letters (+ remaining words)

    // c. prompt guess

    // d. partition words based on family

    // e. find largest family, ...

    // f. reveal word if out of guesses

    // g. congrats

    // 6. play again?
    return 0;
}
