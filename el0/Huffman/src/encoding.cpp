/*
 * antwe841
 * bensu844
 *
 * An implementation of Huffman encoding
 */

#include "encoding.h"
#include <iterator>
#include <queue>
#include <vector>
// TODO: include any other headers you need

using namespace std;

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    freqTable.emplace(PSEUDO_EOF, 1);
    int character = input.get();
    while (character != -1) {
        // If char already in map, increment value
        auto findChar = freqTable.find(character);
        if (findChar != freqTable.end()) {
            findChar->second += 1;
        }
        // else, create new
        else {
            freqTable.emplace(character, 1);
        }
        // Get next letter
        character = input.get();
    }
    return freqTable;
}

class Compare {
public:
    bool operator() (HuffmanNode* l, HuffmanNode* r){
        return l->count > r->count;
    }
};

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    std::priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> queue;

    // Add all chars to queue as nodes
    for (auto it = freqTable.begin(); it != freqTable.end(); it++){
        HuffmanNode* node = new HuffmanNode(it->first, it->second, nullptr, nullptr);
        queue.push(node);
    }

    while (queue.size() >= 2){
        // Get two smallest
        HuffmanNode* leftChildptr = queue.top();
        queue.pop();


        HuffmanNode* rightChildptr = queue.top();
        queue.pop();

        // Create new node with two smallest as children
        HuffmanNode* newNode = new HuffmanNode(NOT_A_CHAR, leftChildptr->count + rightChildptr->count, leftChildptr, rightChildptr);
        queue.push(newNode);
    }

    HuffmanNode* rootptr = queue.top();
    return rootptr;
}

void traverseTree(const HuffmanNode* root, const string& path, map<int, string>& map){
    if(root->isLeaf()) {
        map.emplace(root->character, path);
    } else {
        string newPath = path;
        traverseTree(root->zero, newPath.append("0") , map);

        newPath = path;
        traverseTree(root->one, newPath.append("1") , map);
    }
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    string emptyString = "";

    traverseTree(encodingTree, emptyString, encodingMap);

    return encodingMap;
}

void writeCharacter(int character, const map<int, string> &encodingMap, obitstream& output){
    for(char c : encodingMap.at(character)){
        output.writeBit(c - '0');    // convert ascii-coded char to int 0 or 1
    }
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    int character = input.get();
    while(character != -1){
        writeCharacter(character, encodingMap, output);
        character = input.get();
    }

    writeCharacter(PSEUDO_EOF, encodingMap, output);
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    int bit = input.readBit();
    HuffmanNode* currentNode = encodingTree;

    while(bit != -1){
        if(bit == 0){
            currentNode = currentNode->zero;
        } else {
            currentNode = currentNode->one;
        }

        if (currentNode->isLeaf()){
            output.put(currentNode->character);
            currentNode = encodingTree;
        }

        bit = input.readBit();
    }
}

void writeInteger(int n, obitstream& output){
    string s = to_string(n);
    for(char digit : s){
        output.put(digit);
    }
}

void writeHeader(map<int, int> frequencyTable, obitstream& output){
    bool firstStep = true;

    output.put('{');
    for (pair<int, int> pair : frequencyTable){
        if(!firstStep){
            output.put(',');
            output.put(' ');
        } else {
            firstStep = false;
        }

        // Write character
        writeInteger(pair.first, output);
        output.put(':');
        // Write count
        writeInteger(pair.second, output);

    }
    output.put('}');
}

void compress(istream& input, obitstream& output) {
    map<int, int> frequencyTable = buildFrequencyTable(input);
    HuffmanNode* encodingTree = buildEncodingTree(frequencyTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);

    writeHeader(frequencyTable, output);

    input.clear();              // removes any current eof/failure flags
    input.seekg(0, ios::beg);   // tells the stream to seek back to the beginning

    encodeData(input, encodingMap, output);


}


map<int, int> readHeader(ibitstream& input){
    map<int, int> frequencyTable= {};
    char byte = input.get();
    bool readingToCharacter = true;
    string character = "";
    string count = "";

    while (byte != '}'){
        byte = input.get();
        if(byte == '}'){
            frequencyTable.emplace(stoi(character), stoi(count));
        } else if (byte == ':'){
            readingToCharacter = false;
            // switch
        } else if (byte == ','){
            input.get();    // Remove space after comma
            readingToCharacter = true;
            // store values to map
            frequencyTable.emplace(stoi(character), stoi(count));
            character = "";
            count = "";
        } else {
            if(readingToCharacter){
                character.push_back(byte);
            } else {
                count.push_back(byte);
            }
        }
    }

    return frequencyTable;
}


void decompress(ibitstream& input, ostream& output) {
    map<int, int> frequencyTable = readHeader(input);
    HuffmanNode* encodingTree = buildEncodingTree(frequencyTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);

    decodeData(input, encodingTree, output);
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
