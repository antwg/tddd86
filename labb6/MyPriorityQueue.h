// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

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
    int leftChild(const int i);

    /**
     * Returns the index of the node with index i:s right child, if outside scope, return null.
     */
    int rightChild(const int i);

    /**
     * Returns true if node is a leaf, else false
     */
    bool isLeaf(const int i);

    /**
     * Returns the index of the node with index i:s parent, if outside scope, return null.
     */
    int parent(const int i);

    /**
     * Swaps the elements at position i and j in vector_array.
     */
    void swap(const int i, const int j);
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
    int curr = vector_array.size();
    while ((curr != 0) && (vector_array[curr].strictly_larger_than(vector_array[parent(curr)]) > 0)){
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
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.size() > 0;
}

template <typename T, typename C>
int MyPriorityQueue<T, C>::leftChild(const int i){
    if (2 * i + 1 >= vector_array.size()){
        return (int) NULL;
    }
    return 2 * i + 1;
}

template <typename T, typename C>
int MyPriorityQueue<T, C>::rightChild(const int i){
    if (2 * i + 2 >= vector_array.size()){
        return (int) NULL;
    }
    return 2 * i + 2;
}

template <typename T, typename C>
bool MyPriorityQueue<T, C>::isLeaf(const int i){
    return (i < vector_array.size()) && (2 * i + 1 > vector_array.size());
}

template <typename T, typename C>
int MyPriorityQueue<T, C>::parent(const int i){
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

#endif // MY_PRIORITY_QUEUE_H
