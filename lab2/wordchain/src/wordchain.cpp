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
    file.close();
}

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

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    string words;
    cout << "Please type two words: ";
    getline(cin, words);
    vector<string> x;
    string word1;
    string word2;
    splitWords(words, word1, word2);



    set<string> dict;
    getDict(dict);
    //cout << "Dict size: " << dict.size() << endl;


    cout << "Have a nice day." << endl;
    return 0;
}
