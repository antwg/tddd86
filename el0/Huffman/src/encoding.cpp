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

bool compare(HuffmanNode l, HuffmanNode r){
    return l.count > r.count;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    // TODO Sorterar efter address, inte count, av nån jävla anledning
    std::priority_queue<HuffmanNode> queue;
    // Add all chars to queue as nodes
    for (auto it = freqTable.begin(); it != freqTable.end(); it++){
        HuffmanNode node = HuffmanNode(it->first, it->second, nullptr, nullptr);
        queue.push(node);
    }
    while (queue.size() >= 2){
        // Get two smallest
        HuffmanNode leftChild = queue.top();
        HuffmanNode* leftChildptr = &leftChild;
        queue.pop();

        HuffmanNode rightChild = queue.top();
        HuffmanNode* rightChildptr = &rightChild;
        queue.pop();

        // Create new node with two smallest as children
        HuffmanNode newNode = HuffmanNode(NOT_A_CHAR, leftChild.count + rightChild.count, leftChildptr, rightChildptr);
        queue.push(newNode);
    }
    HuffmanNode root = queue.top();
    HuffmanNode* rootptr = & root;
    return rootptr;
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    map<int, string> encodingMap;
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
