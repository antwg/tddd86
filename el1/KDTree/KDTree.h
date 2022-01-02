/**
 * File: KDTree.h
 * Author: antwe841, bensu844
 * ------------------------
 * An interface representing a kd-tree in some number of dimensions. The tree
 * can be constructed from a set of data and then queried for membership and
 * nearest neighbors.
 */

#ifndef KDTREE_INCLUDED
#define KDTREE_INCLUDED

#include "Point.h"
#include "BoundedPQueue.h"
#include <stdexcept>
#include <cmath>

using namespace std;

// ------------------------------------- Node ------------------------------------------------

template <size_t N, typename ElemType>
class Node {
public:
    /*
     * Constructor
     * Takes a point, a value and a parent node. Sets children to null_ptr
     */
    Node(const Point<N>& pt, const ElemType& val, const Node* parent);

    /*
     * Destructor
     * Destroys its children, then itself
     */
    ~Node();

    /*
     * Copy constructor
     * Creates a copy of a node
     */
    Node(const Node* rhs);

    Point<N> point;
    ElemType value;
    int depth;
    Node* leftChild = nullptr;
    Node* rightChild = nullptr;
};

template <size_t N, typename ElemType>
Node<N, ElemType>::Node(const Point<N>& pt, const ElemType& val, const Node* parent) {
    point = pt;
    value = val;
    if (parent == nullptr) {
        depth = 0;
    } else {
        depth = parent->depth + 1;
    }
}

template <size_t N, typename ElemType>
Node<N, ElemType>::~Node() {
    delete leftChild;
    delete rightChild;
}

template <size_t N, typename ElemType>
Node<N, ElemType>::Node(const Node* rhs) {
    point = rhs->point;
    value = rhs->value;
    depth = rhs->depth;

    if (rhs->leftChild != nullptr){
        leftChild = new Node<N, ElemType>(rhs->leftChild);
    }
    if (rhs->rightChild != nullptr){
        rightChild = new Node<N, ElemType>(rhs->rightChild);
    }
}

// ------------------------------------- KDTree ------------------------------------------------

template <size_t N, typename ElemType>
class KDTree {
public:
    // Constructor: KDTree();
    // Usage: KDTree<3, int> myTree;
    // ----------------------------------------------------
    // Constructs an empty KDTree.
    KDTree();
    
    // Destructor: ~KDTree()
    // Usage: (implicit)
    // ----------------------------------------------------
    // Cleans up all resources used by the KDTree.
    ~KDTree();
    
    // KDTree(const KDTree& rhs);
    // KDTree& operator=(const KDTree& rhs);
    // Usage: KDTree<3, int> one = two;
    // Usage: one = two;
    // -----------------------------------------------------
    // Deep-copies the contents of another KDTree into this one.
    KDTree(const KDTree& rhs);
    KDTree& operator=(const KDTree& rhs);
    
    // size_t dimension() const;
    // Usage: size_t dim = kd.dimension();
    // ----------------------------------------------------
    // Returns the dimension of the points stored in this KDTree.
    size_t dimension() const;
    
    // size_t size() const;
    // bool empty() const;
    // Usage: if (kd.empty())
    // ----------------------------------------------------
    // Returns the number of elements in the kd-tree and whether the tree is
    // empty.
    size_t size() const;
    bool empty() const;
    
    // bool contains(const Point<N>& pt) const;
    // Usage: if (kd.contains(pt))
    // ----------------------------------------------------
    // Returns whether the specified point is contained in the KDTree.
    bool contains(const Point<N>& pt) const;
    
    // void insert(const Point<N>& pt, const ElemType& value);
    // Usage: kd.insert(v, "This value is associated with v.");
    // ----------------------------------------------------
    // Inserts the point pt into the KDTree, associating it with the specified
    // value. If the element already existed in the tree, the new value will
    // overwrite the existing one.
    void insert(const Point<N>& pt, const ElemType& value);
    
    // ElemType& operator[](const Point<N>& pt);
    // Usage: kd[v] = "Some Value";
    // ----------------------------------------------------
    // Returns a reference to the value associated with point pt in the KDTree.
    // If the point does not exist, then it is added to the KDTree using the
    // default value of ElemType as its key.
    ElemType& operator[](const Point<N>& pt);
    
    // ElemType& at(const Point<N>& pt);
    // const ElemType& at(const Point<N>& pt) const;
    // Usage: cout << kd.at(v) << endl;
    // ----------------------------------------------------
    // Returns a reference to the key associated with the point pt. If the point
    // is not in the tree, this function throws an out_of_range exception.
    ElemType& at(const Point<N>& pt);
    const ElemType& at(const Point<N>& pt) const;
    
    // ElemType kNNValue(const Point<N>& key, size_t k) const
    // Usage: cout << kd.kNNValue(v, 3) << endl;
    // ----------------------------------------------------
    // Given a point v and an integer k, finds the k points in the KDTree
    // nearest to v and returns the most common value associated with those
    // points. In the event of a tie, one of the most frequent value will be
    // chosen.
    ElemType kNNValue(const Point<N>& key, size_t k) const;

private:
    size_t treeSize;
    Node<N, ElemType>* root;

    /*
     * Finds a node and returns a pointer to said node
     */
    Node<N, ElemType>* findNode(const Point<N>& pt) const;
};

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree() {
    treeSize = 0;
    root = nullptr;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
    if (root != nullptr){
        delete root;
    }
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree& rhs) {
    treeSize = rhs.treeSize;
    root = new Node<N, ElemType>(rhs.root);
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>& KDTree<N, ElemType>::operator=(const KDTree& rhs){
    if (this == &rhs){ // Allows chaining
        return *this;
    }

    treeSize = rhs.treeSize;

    delete root;
    root = new Node<N, ElemType>(rhs.root);
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
    return N;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const {
    return treeSize;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const {
    return treeSize == 0;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N>& pt) const {
    return findNode(pt) != nullptr;
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N>& pt, const ElemType& value) {
    // If tree empty, create new root node
    if (root == nullptr) {
        root = new Node<N,ElemType>(pt, value, nullptr);
        treeSize++;
        return;
    }

    int currIndex = 0;
    Node<N, ElemType>* currNode = root;
    while (currNode->point != pt){
        currIndex = currNode->depth % N;
        // Choose child to compare
        if (pt[currIndex] > currNode->point[currIndex]){
            // If child doesnt exist, create new
            if (currNode->rightChild == nullptr){
                currNode->rightChild = new Node<N, ElemType>(pt, value, currNode);
                treeSize++;
                return;
            }
            // Else recurse
            currNode = currNode->rightChild;
        }
        else {
            // If child doesnt exist, create new
            if (currNode->leftChild == nullptr){
                currNode->leftChild = new Node<N, ElemType>(pt, value, currNode);
                treeSize++;
                return;
            }
            // Else recurse
            currNode = currNode->leftChild;
        }
    }
    // If found, override value
    currNode->value = value;
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt) {
    Node<N, ElemType>* node = findNode(pt);

    if (node == nullptr) {
        insert(pt, {});
        node = findNode(pt);
        return node->value;
    }

    return node->value;
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) {
    Node<N, ElemType>* node = findNode(pt);

    if (node == nullptr) {
        throw out_of_range ("Point is not in the tree!");
    }

    return node->value;
}

template <size_t N, typename ElemType>
const ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) const {
    Node<N, ElemType>* node = findNode(pt);

    if (node == nullptr) {
        throw out_of_range ("Point is not in the tree!");
    }

    return node->value;
}

template <size_t N, typename ElemType>
void search(const Point<N> key, BoundedPQueue<Node<N, ElemType>*>& bpq, Node<N, ElemType>* curr){
    if (curr == nullptr){
        return;
    }

    bpq.enqueue(curr, Distance(curr->point, key));

    int currIndex = curr->depth % N;

    Node<N, ElemType>* nextNode;
    Node<N, ElemType>* otherNode;

    if (key[currIndex] < curr->point[currIndex]){
        nextNode = curr->leftChild;
        otherNode = curr->rightChild;
    } else {
        nextNode = curr->rightChild;
        otherNode = curr->leftChild;
    }

    search(key, bpq, nextNode);

    bool bpqFull = bpq.size() >= bpq.maxSize();
    double dist = abs(curr->point[currIndex] - key[currIndex]);
    if(!bpqFull || dist < bpq.worst()){
        search(key, bpq, otherNode);
    }
}

template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::kNNValue(const Point<N>& key, size_t k) const {
    BoundedPQueue<Node<N, ElemType>*> bpq = BoundedPQueue<Node<N, ElemType>*>(k);

    Node<N, ElemType>* curr = root;

    // Get 5 closest neighbors
    search(key, bpq, curr);

    map<ElemType, int> values;
    ElemType mostCommonVal;
    int occurences = 0;

    // Find most common value of neighbors
    while (!bpq.empty()){
        ElemType nextVal = bpq.dequeueMin()->value;

        if(values.count(nextVal) >= 1){
            values[nextVal]++;
        } else {
            values.emplace(nextVal, 1);
        }

        if (values[nextVal] > occurences){
            occurences = values[nextVal];
            mostCommonVal = nextVal;
        }
    }

    return mostCommonVal;
}

template <size_t N, typename ElemType>
Node<N, ElemType>* KDTree<N, ElemType>::findNode(const Point<N>& pt) const {
    if (this->empty()){
        return nullptr;
    }
    int currIndex = 0;
    Node<N, ElemType>* currNode = root;
    // While not found
    while (currNode->point != pt){
        currIndex = currNode->depth % N;
        // If pt > currNode
        if (pt[currIndex] > currNode->point[currIndex]){
            // If no child, return
            if (currNode->rightChild == nullptr){
                return nullptr;
            }
            // else recurse
            currNode = currNode->rightChild;
        }
        else {
            // If no child, return
            if (currNode->leftChild == nullptr){
                return nullptr;
            }
            // else, recurse
            currNode = currNode->leftChild;
        }
    }
    // If found, return node
    return currNode;
}

#endif // KDTREE_INCLUDED
