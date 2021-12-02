/*
 * antwe841
 * bensu844
 *
 * A general implementation of the ADS priority queue.
 */

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"


template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    /**
     * Constructor
     */
    MyPriorityQueue();

    /**
     * Destructor
     */
    ~MyPriorityQueue();

    /**
     * Adds t to the priority queue
     * Inspired by https://www.ida.liu.se/opendsa/Books/TDDD86F21/html/Heaps.html
     */
    void push(const T& t);

    /**
     * Returns the element with the highest priority in the queue.
     */
    T top()const;

    /**
     * Removes the element with the highest priority from the queue.
     * Inspired by https://www.ida.liu.se/opendsa/Books/TDDD86F21/html/Heaps.html
     */
    void pop();

    /**
     * Returns true if the queue contains no elements, otherwise false.
     */
    bool empty()const;

private:

    /**
     * Returns the index of the node with index i:s left child, if outside scope, return null.
     */
    int leftChild(const unsigned i);

    /**
     * Returns the index of the node with index i:s right child, if outside scope, return null.
     */
    int rightChild(const unsigned i);

    /**
     * Returns true if node is a leaf, else false
     */
    bool isLeaf(const unsigned i);

    /**
     * Returns the index of the node with index i:s parent, if outside scope, return null.
     */
    int parent(const unsigned i);

    /**
     * Swaps the elements at position i and j in vector_array.
     */
    void swap(const int i, const int j);

    /**
     * Puts the element at index pos at the correct index.
     * Inspired by https://www.ida.liu.se/opendsa/Books/TDDD86F21/html/Heaps.html
     */
    void siftdown(unsigned pos);
};

template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
    vector_array = MyVector<T>();
}

template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
    // TODO: replace the code below with your code for this member
    // MYEXCEPTION("unimplemented method");
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);
    int curr = vector_array.size() - 1;
    while ((curr != 0) && (strictly_larger_operator(vector_array[curr], vector_array[parent(curr)]))){
        swap(curr, parent(curr));
        curr = parent(curr);
    }

}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    if (vector_array.empty()) return;
    swap(0, vector_array.size() - 1);   // Swap root and last element
    vector_array.pop_back();        // Remove last element
    if (!vector_array.empty()){
        siftdown(0);
    }

}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.size() > 0;
}

template <typename T, typename C>
int MyPriorityQueue<T, C>::leftChild(const unsigned i){
    if (2 * i + 1 >= vector_array.size()){
        return (int) NULL;
    }
    return 2 * i + 1;
}

template <typename T, typename C>
int MyPriorityQueue<T, C>::rightChild(const unsigned i){
    if (2 * i + 2 >= vector_array.size()){
        return (int) NULL;
    }
    return 2 * i + 2;
}

template <typename T, typename C>
bool MyPriorityQueue<T, C>::isLeaf(const unsigned i){
    return (i < vector_array.size()) && (2 * i + 1 > vector_array.size());
}

template <typename T, typename C>
int MyPriorityQueue<T, C>::parent(const unsigned i){
    if (i == 0){
        return (int) NULL;
    }
    return ((i - 1) / 2);
}

template <typename T, typename C>
void MyPriorityQueue<T, C>::swap(const int i, const int j){
    T temp = vector_array[i];
    vector_array[i] = vector_array[j];
    vector_array[j] = temp;
}

template <typename T, typename C>
void MyPriorityQueue<T, C>::siftdown(unsigned pos){
    if ((pos < 0) || (pos >= vector_array.size())) { // Out of bounds
        return;
    }
    while (!isLeaf(pos)){
        // Choose largest child
        unsigned child = leftChild(pos);
        if (child < (vector_array.size() - 1) && (!strictly_larger_operator(vector_array[child], vector_array[child + 1]))){
            child++; // Right child
        }
        // If node larger than child, return, else continue
        if (strictly_larger_operator(vector_array[child], vector_array[child])){
            return;
        }
        // Swap and move down
        swap(pos, child);
        pos = child;
    }
}

#endif // MY_PRIORITY_QUEUE_H
