/*
 * antwe841
 * bensu844
 *
 * MyVector is an implementation of the Vector data structure.
 */


#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"
#include <iostream>

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
    T* arr = new T[1];
    int arraySize = 0;
    int capacity = 1;
};

template<typename T>
MyVector<T>::MyVector() : arraySize(0) , capacity(1){
    for (int i = 0; i < capacity; i++){
        arr[i] = 0;
    }
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] arr;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other) : arraySize(other.arraySize), capacity(other.capacity){
    for (int i; i < other.arraySize; i++){
        arr[i] = other.arr[i];
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if (this == &other) // Allows chaining
        return *this;

    arraySize = other.arraySize;
    capacity = other.capacity;
    for (int i; i < other.arraySize; i++){
        arr[i] = other.arr[i];
    }
    return *this;
}


template<typename T>
void MyVector<T>::push_back(const T& e){
    if (arraySize == capacity){
        T* newArray = new T[capacity * 2];
        capacity *= 2;
        for (int i = 0; i < arraySize; i++){
            newArray[i] = arr[i];
        }
        delete[] arr;
        arr = newArray;
    }
    arr[arraySize] = e;
    arraySize++;
    int a = 0;
    for (int i = 0; i < arraySize; i++){
        a++;
    }
}

template<typename T>
void MyVector<T>::pop_back(){
    arr[arraySize] = 0;
    arraySize--;
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return arr[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return arr[i];  // const ???
}

template<typename T>
bool MyVector<T>::empty()const{
    return arraySize == 0;
}

template<typename T>
void MyVector<T>::clear(){
    arraySize = 0;
    capacity = 1;

    delete[] arr;
    arr = new T[1];
}

template<typename T>
unsigned MyVector<T>::size()const{
    return arraySize;
}

template<typename T>
T* MyVector<T>::begin(){
    return &arr[0];
}

template<typename T>
T* MyVector<T>::end(){
    return &arr[arraySize];
}

#endif // MY_VECTOR_H
