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

    const T& operator[](unsigned i)const;

    void remove(unsigned i);

    bool empty()const;

    T* begin();

    T* end();

    void clear();

    unsigned size()const;

private:

    // private members?

};

template<typename T>
MyVector<T>::MyVector(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
MyVector<T>::~MyVector(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
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
