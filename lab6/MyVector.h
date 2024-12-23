
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    //Creates empty vector
    MyVector();

    //Destructor
    ~MyVector();

    //Copy constructor
    MyVector(const MyVector& other);

    //Assignment operator
    MyVector& operator =(const MyVector& other);

    //Push_back element on vector
    void push_back(const T&);

    //Pop_back element on vector
    void pop_back();

    //Index operator
    T& operator[](unsigned i);

    //Const index operator
    const T& operator[](unsigned i)const;

    //Checks if vector is empty, then return true
    bool empty()const;

    //Pointer to the first element
    T* begin();

    //Pointer to the last emelent
    T* end();

    //Clears all elemtens in the vector
    void clear();

    //Returns the number of elements in the vector
    unsigned size()const;

private:
    T* storage;
    unsigned capacity = 1;
    unsigned elements = 0;

    //Doubles the array of the storage
    void doubbleArray();

    //Copies the storage
    void copy(const MyVector& other);

};

template<typename T>
MyVector<T>::MyVector(){
    storage = new T[1];
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] storage;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    copy(other);
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if (this != &other) {
        delete[] storage;
        copy(other);
    }
    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){
   //0(1)
   if (capacity <= size()) {
       doubbleArray();
   }
   storage[size()] = e;
   elements++;

   //0(N)
   /*for (int i = elements - 1; i >= 1; i--) {
       storage[i] = storage[i];
   }*/
}

template<typename T>
void MyVector<T>::pop_back(){
    if (size() == 0) {
        return;
    }
    elements--;
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return storage[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return storage[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    return size() == 0;
}

template<typename T>
void MyVector<T>::clear(){
    elements = 0;
    capacity = 1;
    delete[] storage;
    storage = new T[1];
}

template<typename T>
unsigned MyVector<T>::size()const{
    return elements;
}

template<typename T>
T* MyVector<T>::begin(){
    return &storage[0];
}

template<typename T>
T* MyVector<T>::end(){
    return &storage[size()];
}

template<typename T>
void MyVector<T>::doubbleArray() {
    T* newArray = new T[capacity * 2];
    for (unsigned i = 0; i < size(); i++) {
        newArray[i] = storage[i];
    }
    delete[] storage;
    storage = newArray;
    capacity *= 2;
}

template<typename T>
void MyVector<T>::copy(const MyVector &other) {
    storage = new T[other.capacity];
    elements = other.elements;
    capacity = other.capacity;
    for (int i = 0; i < other.size(); i++) {
        storage[i] = other.storage[i];
    }
}


#endif // MY_VECTOR_H
