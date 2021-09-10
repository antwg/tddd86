#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void getDict(set<string>& dict){
    ifstream file("dictionary.txt");
    string line;
    while (getline(file, line)){
        dict.insert(line);
    }
}


stack<string> wordChain(string w1, string w2){
    set<string> dictionary;
    getDict(dictionary);

    queue<stack<string>> queue;     // create an empty queue of stacks
    stack<string> firstStack;       // create/add a stack containing {w1} to the queue
    firstStack.push(w1);
    queue.push(firstStack);

    dictionary.
    while (!queue.empty()) {        // while the queue is not empty:
        stack<string> currentStack = queue.front();     // dequeue the partial-chain stack from the front of the queue
        queue.pop();

        if (currentStack.top() == w2){      // if the word at the top of the stack is the destinaction word:
            return currentStack;            // hooray! output the elements of the stack as the solution
        } else {
            // for each valid English word that is a neighbour (differs by 1 letter) of the word at the top of the stack:
            for (int i = 0; i < currentStack.top().length(); i++) {
                for (auto c : ALPHABET){
                    string neighbourWord = currentStack.top();
                    neighbourWord[i] = c;
                    if (dictionary.count(neighbourWord) != 0) {
                        dictionary.erase(neighbourWord);
                        stack<string> stackCopy = currentStack;     // create a copy of the current chain stack
                        stackCopy.push(neighbourWord);              // put the neighbour word at the top of the copy stack
                        queue.push(stackCopy);                      // add the copy stack to the end of the queue
                    }
                }
            }
        }
    }
    cout << "no valid path to w2" << endl;
    return stack<string>();
}

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    // TODO: Finish the program!

    cout << wordChain("code", "data").top() << endl;

    return 0;
}
