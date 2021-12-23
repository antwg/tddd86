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

// "using namespace" in a header file is conventionally frowned upon, but I'm
// including it here so that you may use things like size_t without having to
// type std::size_t every time.
using namespace std;

template <size_t N, typename ElemType>
class Node {
public:
    Node(const Point<N>& pt, const ElemType& val, const Node* parent);

    ~Node();

    Point<N> point;
    ElemType value;

    Node* leftChild = nullptr;
    Node* rightChild = nullptr;
    const Node* parentNode;
private:

};

template <size_t N, typename ElemType>
Node<N, ElemType>::Node(const Point<N>& pt, const ElemType& val, const Node* parent) {
    point = pt;
    value = val;
    parentNode = parent;
}

template <size_t N, typename ElemType>
Node<N, ElemType>::~Node() {

}



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
    // TODO: Add implementation details here.
    size_t treeSize;
    Node<N, ElemType>* root;

    Node<N, ElemType>* findNode(const Point<N>& pt) const;
};

/** KDTree class implementation details */

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree() {
    treeSize = 0;
    root = nullptr;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
    // TODO: Fill this in.
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
    treeSize++;
    if (root == nullptr) {
        root = new Node<N,ElemType>(pt, value, nullptr);
        return;
    }
    Node<N, ElemType>* node = findNode(pt);
    int n = 0;
    Node<N, ElemType>* currNode = root;
    while (currNode->point != pt){
        if (pt[n] > currNode->point[n]){
            if (currNode->rightChild == nullptr){
                currNode->rightChild = new Node<N, ElemType>(pt, value, currNode);
                return;
            }
            currNode = currNode->rightChild;
        }
        else {
            if (currNode->leftChild == nullptr){
                currNode->leftChild = new Node<N, ElemType>(pt, value, currNode);
                return;
            }
            currNode = currNode->leftChild;
        }
        n = (n + 1) % N;
    }
    currNode->value = value;
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt) {
    Node<N, ElemType>* node = findNode(pt);

    if (node == nullptr) {
        insert(pt, {});
        node = findNode(pt);    // TODO: look at this again
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
ElemType KDTree<N, ElemType>::kNNValue(const Point<N>& key, size_t k) const {
    // TODO: Fill this in.
}

template <size_t N, typename ElemType>
Node<N, ElemType>* KDTree<N, ElemType>::findNode(const Point<N>& pt) const {
    if (this->empty()){
        return nullptr;
    }
    int n = 0;
    Node<N, ElemType>* currNode = root;
    while (currNode->point != pt){
        if (pt[n] > currNode->point[n]){
            if (currNode->rightChild == nullptr){
                return nullptr;
            }
            currNode = currNode->rightChild;
        }
        else {
            if (currNode->leftChild == nullptr){
                return nullptr;
            }
            currNode = currNode->leftChild;
        }
        n = (n + 1) % N;
    }
    return currNode;
}

// TODO: finish the implementation of the rest of the KDTree class

#endif // KDTREE_INCLUDED
