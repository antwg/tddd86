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

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    // TODO: Finish the program!

    set<string> dict;
    getDict(dict);
    cout << "Dict size: " << dict.size() << endl;

    return 0;
}
