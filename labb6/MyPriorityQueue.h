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
     * Returns the index of the node with index i:s left child
     */
    int leftChild(int i);

    /**
     * Returns the index of the node with index i:s right child
     */
    int rightChild(int i);

    /**
     * Returns the index of the node with index i:s parent
     */
    int parent(int i);
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

}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

#endif // MY_PRIORITY_QUEUE_H
