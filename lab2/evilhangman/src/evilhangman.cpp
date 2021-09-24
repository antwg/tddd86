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
    ifstream file("dictionary.txt");
    //ifstream file("di.txt");
    string line;
    while (getline(file, line)){
        dict.insert(line);
    }
    file.close();
}

/*
 * Gets all words of a given length from a dictionary and adds them to a possibleWords.
 */
void getWordsOfLength(const unsigned& length, const unordered_set<string>& dict, set<string>& possibleWords){
    for (const auto& word: dict){
        if (word.length() == length){
            possibleWords.insert(word);
        }
    }
}

/*
 * Asks for a word length. Saves length if valid, else asks again.
 */
void getWordLength(const unordered_set<string>& dict, set<string>& possibleWords, int& wordLength){
    cout << "Please enter a word length: ";
    cin >> wordLength;
    getWordsOfLength(wordLength, dict, possibleWords);
    if (possibleWords.empty()){
        cout << "No words of given length." << endl;
        getWordLength(dict, possibleWords, wordLength);
    }
}

/*
 * Asks for how many guesses the user wants. Returns the number of guesses if it's > 1, else asks again.
 */
int getNumberOfGuesses(){
    int numberOfGuesses;
    cout << "Enter number of guesses: ";
    cin >> numberOfGuesses;
    if (numberOfGuesses < 1) {
        numberOfGuesses = getNumberOfGuesses();
    }
    return numberOfGuesses;
}

/*
 * Asks the user if the number of remaining words are to be shown, if "yes", return true, else false.
 */
bool getShowRemainingWords(){
    cout << "Do you want to see the number of remaining words? ";
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

/*
 * Asks the user for a guess. If the guess is a single letter, is in the alphabet and hasn't been guessed before,
 * it's saved, else asks for another letter.
 */
void askForGuess(string& guessedLetters, string& guess){
    cout << "Please enter a letter: ";
    cin >> guess;
    if (guess.length() != 1 || ALPHABET.find(guess) == string::npos || guessedLetters.find(guess) != string::npos){
        askForGuess(guessedLetters, guess);
    }
    guessedLetters.append(guess);
    cout << endl;
}

/*
 * Converts word from a string to an int. If a letter in word is the same as guess, it gets the value 1, else 0.
 * For example: word = code, guess = d would return 0010 = 2.
 */
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

/*
 * Makes wordProgress a string of '-' of length wordLength.
 */
void resetWordProgress(string& wordProgress, const int& wordLength){
    for (int j = 0; j < wordLength; j++){
        wordProgress.push_back('-');
    }
}

/*
 * Gives all words a key in the form of an int. The bits in the int represent what family the word is in.
 * All words in the same family have the same key.
 */
void partitionWords(const set<string>& possibleWords, multimap<int, string>& partitions, const string& guess){
    for (string word : possibleWords){
        partitions.emplace(stringToBits(word, guess), word);
    }
}

/*
 * Finds and returns the key of the biggest partition.
 */
long findBiggestPartition(const int wordLength, const multimap<int, string>& partitions)
{
    long biggestPartitionKey = 0;
    unsigned biggestPartitionSize = 0;
    for (long key = 0; key < 1 << wordLength; key++) {
        if (partitions.count(key) > biggestPartitionSize) {
            biggestPartitionSize = partitions.count(key);
            biggestPartitionKey = key;
        }
    }

    return biggestPartitionKey;
}

/*
 * Updates the wordProgress string based on the guess.
 */
void updateWordProgress(const long biggestPartitionKey, const int wordLength, string& wordProgress, const string& guess, int& remainingGuesses)
{
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
}

/*
 * Prints info about the game state to the console.
 */
void printEndOfStep(int remainingGuesses, set<string> possibleWords, bool showRemainingWords, string wordProgress, string guessedLetters)
{
    // b. print remaining guesses + guessed letters (+ remaining words)
    cout << "You have " << remainingGuesses << " guesses left." << endl;
    cout << "Guessed letters: " << guessedLetters << endl;
    cout << "Word progress: " << wordProgress << endl;
    if (showRemainingWords) {
        cout << "Remaining words: " << possibleWords.size() << endl;
    }
}

/*
 * The main functionality of the game
 */
void onStep(int& wordLength, string& wordProgress, string& guessedLetters, bool& showRemainingWords, string& guess, int& remainingGuesses, set<string>& possibleWords)
{
    cout << endl << "===========================" << endl;
    askForGuess(guessedLetters, guess);

    // Partition words based on family
    multimap<int, string> partitions;
    partitionWords(possibleWords, partitions, guess);

    // e. find largest family, ...
    long biggestPartitionKey = findBiggestPartition(wordLength, partitions);

    possibleWords.clear();
    for (auto pair : partitions){
        if(pair.first == biggestPartitionKey){
            possibleWords.insert(pair.second);
        }
    }

    //update wordProgress
    updateWordProgress(biggestPartitionKey, wordLength, wordProgress, guess, remainingGuesses);

    printEndOfStep(remainingGuesses, possibleWords, showRemainingWords, wordProgress, guessedLetters);
}

/*
 * The game Evil Hangman.
 */
int main() {
    int wordLength;
    string wordProgress;
    string guess;
    string guessedLetters = "";
    unordered_set<string> dict;
    set<string> possibleWords = {};

    cout << "Welcome to Hangman." << endl;

    // Game setup
    getDict(dict);
    getWordLength(dict, possibleWords, wordLength);
    int remainingGuesses = getNumberOfGuesses();
    bool showRemainingWords = getShowRemainingWords();
    resetWordProgress(wordProgress, wordLength);

    // Main game loop
    while (!(possibleWords.size() == 1 && wordProgress == *possibleWords.begin())){
        onStep(wordLength, wordProgress, guessedLetters, showRemainingWords, guess, remainingGuesses, possibleWords);

        if (remainingGuesses == 0) {
            cout << *possibleWords.begin() << endl;
            break;
        }


    }

    cout << "Ended" << endl;

    // g. congrats

    // 6. play again?
    return 0;
}
