// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    /**
     * Constructor
     */
    MyVector();

    /**
     * Destructor
     */
    ~MyVector();

    /**
     * Copy constructor
     */
    MyVector(const MyVector& other);

    /**
     * Equals operator
     */
    MyVector& operator =(const MyVector& other);

    /**
     * Adds an element to the back of the vector.
     */
    void push_back(const T&);

    /**
     * Removes the last element of the vector.
     */
    void pop_back();

    /**
     * [] operator. Returns the i:th element in the vector.
     */
    T& operator[](unsigned i);

    /**
     * Defines the [] operator to point at the i:th element in the vector
     */
    const T& operator[](unsigned i)const;

    /**
     * Removes the element in index i
     */
    void remove(unsigned i);

    /**
     * Returns true if vector is empty, else false
     */
    bool empty()const;

    /**
     * Returns a pointer to the first element in the vector
     */
    T* begin();

    /**
     * Returns a pointer to the last element in the vector
     */
    T* end();

    /**
     * Clears the vectors elements
     */
    void clear();

    /**
     * Returns the size of the vector
     */
    unsigned size()const;

private:
    T arr[1];
    int arraySize = 0;
    int capacity = 1;
};

template<typename T>
MyVector<T>::MyVector() : arraySize(0) , capacity(1){
    for (int i; i < capacity; i++){
        arr[i] = 0;
    }
}

template<typename T>
MyVector<T>::~MyVector(){
    delete arr[capacity];
    delete arraySize;
    delete capacity;

}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::pop_back(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
bool MyVector<T>::empty()const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::clear(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
unsigned MyVector<T>::size()const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
T* MyVector<T>::begin(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
T* MyVector<T>::end(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

#endif // MY_VECTOR_H
