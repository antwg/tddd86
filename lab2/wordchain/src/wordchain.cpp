// Benjamin Sundvall - bensu844
// Anton Wegeström - antwe841
//
// A program that finds the shortest chain of neighbor words between two given words.

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
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

/*
 * Splits the given string into two separate words.
 */
void splitWords(const string& words, string& word1, string& word2){
    vector<string> output;
    string word = "";
    for (auto x : words) {
        if (x == ' '){
            word1 = word;
            word = "";
        }
        else {
            word = word + x;
        }
    }
    word2 = word;
}

/*
 * Finds the shortest chain of neighboring words between w1 and w2.
 */

void wordChain(stack<string>& currentChain, string w1, string w2){
    unordered_set<string> dictionary;
    getDict(dictionary);

    queue<stack<string>> ladderQueue;     // create an empty queue of stacks
    stack<string> firstChain;             // create/add a stack containing {w1} to the queue
    firstChain.push(w1);
    ladderQueue.push(firstChain);

    while (!ladderQueue.empty()) {        // while the queue is not empty:
        currentChain = ladderQueue.front();     // dequeue the partial-chain stack from the front of the queue
        ladderQueue.pop();

        if (currentChain.top() == w2){    // if the word at the top of the stack is the destinaction word:
            return;          // hooray! output the elements of the stack as the solution
        } else {
            // for each valid English word that is a neighbour (differs by 1 letter) of the word at the top of the stack:
            for (unsigned int i = 0; i < currentChain.top().length(); i++) {
                for (auto c : ALPHABET){
                    string neighbourWord = currentChain.top();
                    neighbourWord[i] = c;
                    if (dictionary.count(neighbourWord) != 0) {
                        dictionary.erase(neighbourWord);
                        stack<string> chainCopy = currentChain;     // create a copy of the current chain stack
                        chainCopy.push(neighbourWord);              // put the neighbour word at the top of the copy stack
                        ladderQueue.push(chainCopy);                // add the copy stack to the end of the queue
                    }
                }
            }
        }
    }
    cout << "no valid path to w2" << endl;
}

/*
 * Shows a start message.
 */
void showStartMessage(){
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
}

/*
 * Asks for, and saves, two words given by user into word1 and word2.
 */
void getWords(string& word1, string& word2){
    cout << "Please type two words: ";
    string words;
    ifstream input;
    getline(cin, words);
    splitWords(words, word1, word2);
}

/*
 * Calls wordChain and prints the stack returned by wordChain.
 */
void getResult(const string& word1, const string& word2){
    cout << "Chain from " << word2 << " back to " << word1 << ":" << endl;

    stack<string> ladder;
    wordChain(ladder, word1, word2);
    while (!ladder.empty()){
        cout << ladder.top() << " ";
        ladder.pop();
    }
}

/*
 * A program that finds the shortest chain of neighbor words between two given words.
 */
int main() {
    showStartMessage();
    string word1;
    string word2;
    getWords(word1, word2);
    getResult(word1, word2);

    cout << endl;
    cout << "Have a nice day." << endl;
    return 0;
}
