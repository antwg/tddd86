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
        cout << c - 48 << endl;
        output.writeBit(c - 48);    // convert ascii-coded char to int 0 or 1
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

void writeAscii(int c, obitstream& output){
    for(int i = 0; i < 8; i++){
        output.writeBit((c >> i) & 1);
    }
}

void writeHeader(map<int, string> encodingMap, obitstream& output){
    output.put('{');
    for (pair<int, string> pair : encodingMap){
        // print character
        output.put(':');
        // print count
        output.put(',');
        output.put(' ');
    }
    output.put('}');
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
    map<int, int> frequencyTable = buildFrequencyTable(input);
    HuffmanNode* encodingTree = buildEncodingTree(frequencyTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);

    writeHeader(encodingMap, output);

    input.clear();              // removes any current eof/failure flags
    input.seekg(0, ios::beg);   // tells the stream to seek back to the beginning

    encodeData(input, encodingMap, output);


}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
