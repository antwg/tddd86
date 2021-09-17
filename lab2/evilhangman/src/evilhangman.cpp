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

unordered_set<string> getWordsOfLength(const unsigned length, const unordered_set<string>& dict, unordered_set<string>& possibleWords){
    for (const auto& word: dict){
        if (word.length() == length){
            possibleWords.insert(word);
        }
    }
    return possibleWords;
}

int getWordLength(const unordered_set<string>& dict, unordered_set<string>& possibleWords){
    unsigned length;
    cout << "Please enter a word length!" << endl;
    cin >> length;
    unordered_set<string>words = getWordsOfLength(length, dict, possibleWords);
    if (words.empty()){
        length = getWordLength(dict, possibleWords);
    }
    return length;
}

int getNumberOfGuesses(){
    int numberOfGuesses;
    cout << "Enter number of guesses:" << endl;
    cin >> numberOfGuesses;
    if (numberOfGuesses < 1) {
        numberOfGuesses = getNumberOfGuesses();
    }
    return numberOfGuesses;
}

bool getShowRemainingWords(){
    cout << "Do you want to see the number of remaining words?" << endl;
    string answer;
    cin >> answer;
    if (answer == "yes"){
        return true;
    } else if (answer == "no"){
        return false;
    } else {
        cout << "Invalid answer. Defaulting to no..." << endl;
        return false;
    }
}

string askForGuess(const string& guessedLetters){
    cout << "Please enter a letter! ";
    string letter;
    cin >> letter;
    if (letter.length() != 1 || ALPHABET.find(letter) == string::npos){
        letter = askForGuess(guessedLetters);
    }
    return letter;
}

int main() {
    int remainingGuesses;
    //int remainingWords;
    bool showRemainingWords;
    string wordProgress;
    string guessedLetters = "";
    unordered_set<string> dict;
    getDict(dict);
    unordered_set<string> possibleWords = {};



    cout << "Welcome to Hangman." << endl;


    // TODO: Finish the program!
    // 1. read file



    // TODO: Finish the program!


    // 2. prompt word length
    getWordLength(dict, possibleWords);

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
    cout << "Word progress: " << wordProgress << endl;
    if (showRemainingWords) {
        cout << "Remaining words: " << possibleWords.size() << endl;
    }

    // c. prompt guess
    string guess = askForGuess(guessedLetters);

    // d. partition words based on family

    // e. find largest family, ...

    // f. reveal word if out of guesses

    // g. congrats

    // 6. play again?
    return 0;
}
