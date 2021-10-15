// Benjamin Sundvall - bensu844
// Anton Wegeström - antwe841
//
// An "evil" hangman game where the computer cheats by not choosing a single
// word from the start, but instead stores all the possible words. If possible,
// it chooses words so that the player's guesses are wrong.


#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <map>
#include <vector>
#include <set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
const int GAMELOST = -1;
const int GAMERUNNING = 0;
const int GAMEWON = 1;

// ========================================================================================================
// Functions for setupGame()

/*
 * Opens the dictionary.txt file and loads all words into an unordered set.
 */
void getDict(unordered_set<string>& dict){
    ifstream file("di.txt");
    string line;
    while (getline(file, line)){
        dict.insert(line);
    }
    file.close();
}

/*
 * Asks for a word length. Saves length if valid, else asks again. It then adds all words of the given length to possibleWords.
 */
void askForWordLength(const unordered_set<string>& dict, vector<string>& possibleWords, unsigned& wordLength){
    cout << "Please enter a word length: ";
    cin >> wordLength;

    for (const auto& word : dict){
        if (word.length() == wordLength){
            possibleWords.push_back(word);
        }
    }

    if (possibleWords.empty()){
        cout << "No words of given length." << endl;
        askForWordLength(dict, possibleWords, wordLength);
    }
}

/*
 * Asks for how many guesses the user wants. Returns the number of guesses if it's > 1, else asks again.
 */
int askForNumberOfGuesses(){
    int numberOfGuesses;
    cout << "Enter number of guesses: ";
    cin >> numberOfGuesses;
    if (numberOfGuesses < 1) {
        numberOfGuesses = askForNumberOfGuesses();
    }
    return numberOfGuesses;
}

/*
 * Asks the user if the number of remaining words are to be shown, if "yes", return true, else false.
 */
bool askForShowRemainingWords(){
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
 * Makes wordProgress a string of '-' of length wordLength.
 */
void resetWordProgress(string& wordProgress, const unsigned wordLength){
    for (unsigned i = 0; i < wordLength; i++){
        wordProgress.push_back('-');
    }
}

/*
 * Sets up the game.
 */
void setupGame(const unordered_set<string>& dict, vector<string>& possibleWords, unsigned& wordLength, string& wordProgress, int& remainingGuesses, bool& showRemainingWords){
    askForWordLength(dict, possibleWords, wordLength);
    remainingGuesses = askForNumberOfGuesses();
    showRemainingWords = askForShowRemainingWords();
    resetWordProgress(wordProgress, wordLength);
}

// ========================================================================================================
// Functions for onStep()

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
long stringToBits(const string& word, const string& guess){
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
 * Gives all words a key in the form of an int. The bits in the int represent what family the word is in.
 * All words in the same family have the same key.
 */
void partitionWords(const vector<string>& possibleWords, map<long, vector<string>>& partitions, const string& guess){
    for (string word : possibleWords){
        long bitseq = stringToBits(word, guess);
        if (partitions.count(bitseq) == 0) {
            partitions[bitseq] = vector<string>();
        }
        partitions[bitseq].push_back(word);
    }
}

/*
 * Finds and returns the key of the biggest partition.
 */
void findBiggestPartition(const map<long, vector<string>>& partitions, vector<string>& possibleWords, long& biggestPartitionKey)
{
    unsigned biggestPartitionSize = 0;
    for(auto it = partitions.begin(); it != partitions.end(); it++){
        if (it->second.size() > biggestPartitionSize){
            biggestPartitionSize = it->second.size();
            biggestPartitionKey = it->first;
            possibleWords = it->second;
        }
    }
}

/*
 * Updates the wordProgress string based on the guess.
 */
void updateWordProgress(const long biggestPartitionKey, const unsigned wordLength, string& wordProgress, const string& guess, int& remainingGuesses)
{
    bool correctGuess = false;
    for (unsigned i = 0; i < wordLength; i++){
        int temp = biggestPartitionKey;
        temp &= 1 << i;
        if (temp){
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
void printEndOfStep(const int remainingGuesses, const vector<string>& possibleWords, const bool showRemainingWords, const string& wordProgress, const string& guessedLetters)
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
void onStep(const unsigned& wordLength, string& wordProgress, string& guessedLetters, const bool& showRemainingWords, int& remainingGuesses, vector<string>& possibleWords, int& gameStatus)
{
    cout << endl << "===========================" << endl;
    string guess;
    askForGuess(guessedLetters, guess);

    // Partition words based on family
    map<long, vector<string>>partitions;
    partitionWords(possibleWords, partitions, guess);

    // Find largest family, ...
    long biggestPartitionKey;
    if (remainingGuesses == 1 && partitions.count(0) != 0) {
        biggestPartitionKey = 0;
        possibleWords = partitions[0];
    } else {
        findBiggestPartition(partitions, possibleWords, biggestPartitionKey);
    }


    //update wordProgress
    updateWordProgress(biggestPartitionKey, wordLength, wordProgress, guess, remainingGuesses);

    printEndOfStep(remainingGuesses, possibleWords, showRemainingWords, wordProgress, guessedLetters);

    if (remainingGuesses == 0) {
        gameStatus = GAMELOST;
    } else if (possibleWords.size() == 1) {
        if (*possibleWords.begin() == wordProgress) {
            gameStatus = GAMEWON;
        }
    }
}

// ========================================================================================================
// Other functions

/*
 * Prints a congratulations message.
 */
void gameWon(){
    cout << "Congrats, you won! Do you want to play again?" << endl;
}

/*
 * Reveals the "chosen" word.
 */
void gameLost(const vector<string>& possibleWords){
    cout << "You lost! The word was: " << *possibleWords.begin() << "\nDo you want to play again?" << endl;
}

/*
 * Asks the player if the want to play again
 */
void askPlayAgain(bool& playAgain){
    string answer;
    cin >> answer;
    if (answer == "yes"){
        playAgain = true;
    }
    else {
        playAgain = false;
    }
}

/*
 * The game Evil Hangman.
 */
int main() {
    bool playAgain = true;
    unordered_set<string> dict;
    getDict(dict);
    while (playAgain) {
        unsigned wordLength;
        string wordProgress = "";
        string guess;
        string guessedLetters = "";
        vector<string> possibleWords = {};
        int remainingGuesses;
        bool showRemainingWords;
        int gameStatus = GAMERUNNING;

        setupGame(dict, possibleWords, wordLength, wordProgress, remainingGuesses, showRemainingWords);

        while (gameStatus == GAMERUNNING) {
            onStep(wordLength, wordProgress, guessedLetters, showRemainingWords, remainingGuesses, possibleWords, gameStatus);
        }
        if (gameStatus == GAMELOST) {
            gameLost(possibleWords);
        } else if (gameStatus == GAMEWON) {
            gameWon();
        }
        askPlayAgain(playAgain);
    }
    return 0;
}
