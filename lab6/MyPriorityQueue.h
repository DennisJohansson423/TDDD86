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
    //Default constructor
    MyPriorityQueue() = default;

    //Default destructor
    ~MyPriorityQueue() = default;

    //Pushses element to queue
    void push(const T& t);

    //Returns the top element of the queue
    T top()const;

    //Pops the first elemtn in the queue
    void pop();

    //Checks if the queue is empty, then returns true
    bool empty()const;

    //Returns the queue size
    unsigned size() const;

private:
    //Shift the heap up
    void shiftUp(int index);

    //Shift the heap down
    void shiftDown(int index);
};

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);
    shiftUp(vector_array.size() - 1);
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    if (!vector_array.empty()) {
        return vector_array[0];
    }
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    vector_array[0] = vector_array[size()-1];
    vector_array.pop_back();
    if(!vector_array.empty()){
            shiftDown(0);
        }
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return size() == 0;
}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::shiftUp(int index) {
    int parentIndex = (index - 1) / 2;
    T parent = vector_array[parentIndex];
    T child = vector_array[index];
    if (strictly_larger_operator(parent, child) && index != 0) {
        vector_array[parentIndex] = vector_array[index];
        vector_array[index] = parent;

        shiftUp(parentIndex);
    }
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::shiftDown(int index) {
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = leftChildIndex + 1;
    int smallest = index;
    if (leftChildIndex < vector_array.size() && strictly_larger_operator(vector_array[smallest], vector_array[leftChildIndex])) {
        smallest = leftChildIndex;
    }
    if (rightChildIndex < vector_array.size() && strictly_larger_operator(vector_array[smallest], vector_array[rightChildIndex])) {
        smallest = rightChildIndex;
    }
    if (smallest != index) {
        T temp = vector_array[index];
        vector_array[index] = vector_array[smallest];
        vector_array[smallest] = temp;
        shiftDown(smallest);
    }
}


#endif // MY_PRIORITY_QUEUE_H
