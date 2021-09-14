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

    return 0;
}
