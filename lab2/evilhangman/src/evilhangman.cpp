#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <map>
#include <set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/*
 * Opens the dictionary.txt file and loads all words into an unordered set.
 */
void getDict(unordered_set<string>& dict){
    //ifstream file("dictionary.txt");
    ifstream file("di.txt");
    string line;
    while (getline(file, line)){
        dict.insert(line);
    }
    file.close();
}

void getWordsOfLength(const unsigned length, const unordered_set<string>& dict, set<string>& possibleWords){
    for (const auto& word: dict){
        if (word.length() == length){
            possibleWords.insert(word);
        }
    }
}

void getWordLength(const unordered_set<string>& dict, set<string>& possibleWords, int& wordLength){
    cout << "Please enter a word length!" << endl;
    cin >> wordLength;
    getWordsOfLength(wordLength, dict, possibleWords);
    if (possibleWords.empty()){
        cout << "No words of given length." << endl;
        getWordLength(dict, possibleWords, wordLength);
    }
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

void askForGuess(string& guessedLetters, string& guess){
    cout << "Please enter a letter! ";
    cin >> guess;
    if (guess.length() != 1 || ALPHABET.find(guess) == string::npos || guessedLetters.find(guess) != string::npos){
        askForGuess(guessedLetters, guess);
    }
    guessedLetters.append(guess);
}

int stringToBits(const string& word, const string& guess){
    char guessChar = guess[0];
    long bits = 0;
    for (unsigned i = 0; i < word.length(); i++){
        if (word[i] == guessChar) {
            bits += 1 << i;
        }
    }
    return bits;
}

int main() {
    int remainingGuesses;
    //int remainingWords;
    bool showRemainingWords;
    string wordProgress = "";
    int wordLength;
    string guessedLetters = "";
    unordered_set<string> dict;
    set<string> possibleWords = {};
    string guess;


    cout << "Welcome to Hangman." << endl;

    // 1. read file
    getDict(dict);

    // 2. prompt word length
    getWordLength(dict, possibleWords, wordLength);

    // 3. prompt number of guesses
    remainingGuesses = getNumberOfGuesses();

    // 4. prompt show number of words
    showRemainingWords = getShowRemainingWords();

    // 5. Actual game

    // a. create list of words based on length
    // DONE IN 2.


    for (int j = 0; j < wordLength; j++){
        wordProgress.push_back('-');
    }

    while (!(possibleWords.size() == 1 && wordProgress == *possibleWords.begin())){
    // c. prompt guess
    askForGuess(guessedLetters, guess);

    // d. partition words based on family
    multimap<int, string> partitions;
    for (string word : possibleWords){
        partitions.emplace(stringToBits(word, guess), word);
    }

 // ======================================================================================================
    // e. find largest family, ...
    long biggestPartitionKey = 0;
    unsigned biggestPartitionSize = 0;
    for (long key = 0; key < 1 << wordLength; key++) {
        if (partitions.count(key) > biggestPartitionSize) {
            biggestPartitionSize = partitions.count(key);
            biggestPartitionKey = key;
        }
    }

    bool correctGuess = false;
    for (int i = 0; i < wordLength; i++){
        int temp = biggestPartitionKey;
        temp &= 1 << i;
        if (temp != 0){
            wordProgress[i] = guess[0];
            correctGuess = true;
        }
    }

    if (!correctGuess){
        remainingGuesses--;
    }
    cout << "Biggest: " << biggestPartitionKey << endl;
    //update wordProgress
    possibleWords.clear();
    for (auto pair : partitions){
        if(pair.first == biggestPartitionKey){
            possibleWords.insert(pair.second);
        }
    }

    cout << wordProgress << endl;
    if (remainingGuesses == 0) {
        cout << *possibleWords.begin() << endl;
        break;
    }

    // b. print remaining guesses + guessed letters (+ remaining words)
    cout << "You have " << remainingGuesses << " guesses left." << endl;
    cout << "Guessed letters: " << guessedLetters << endl;
    cout << "Word progress: " << wordProgress << endl;
    if (showRemainingWords) {
        cout << "Remaining words: " << possibleWords.size() << endl;
    }
    }

    cout << "Ended" << endl;

    //possibleWords = content of key

    // f. reveal word if out of guesses

    // g. congrats

    // 6. play again?
    return 0;
}
