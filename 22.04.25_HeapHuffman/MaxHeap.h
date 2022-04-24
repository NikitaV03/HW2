#pragma once
#include "Arr.h"

template <typename T>
class MaxHeap {
    Arr<T> data_; //array
    unsigned int size_;
    bool sorted_;
public:
    MaxHeap() : data_(), size_(0), sorted_(1) {}
    ~MaxHeap() { size_ = 0; }
    void add(T x);
    void heapify(int i = 0); //по умолчанию сортирует всю кучу
    T& operator[](int ind);
    T delEl(int ind);
    const int size() const { return size_; }
};


template <typename T>
void MaxHeap<T>::add(T x) {
    data_.push_back(x);
    int i = size_;
    int parent = (i - 1) / 2;
    while (i > 0 && data_[parent] < data_[i]) { // поднимаем бќльшие элементы вверх
        T tmp = data_[i];
        data_[i] = data_[parent];
        data_[parent] = tmp;
        i = parent;
        parent = (i - 1) / 2;
    }
    ++size_;
}

template <typename T>
void MaxHeap<T>::heapify(int i) { 
    int leftChild;
    int rightChild;
    int largestChild = i + 1;
    int parent;
    while (largestChild != i) {
        leftChild = 2 * i + 1;
        rightChild = 2 * i + 2;
        largestChild = i;
        parent = (i - 1) / 2;
        //std::cout << "m here " << size_ << std::endl;
        bool leftmorethanright;
        if (rightChild < size_) {
            leftmorethanright = (data_[leftChild] > data_[rightChild]);
        }
        else if (leftChild < size_){
            leftmorethanright = 1;
        }
        else {
            leftmorethanright = 0;
        }
        if (leftChild < size_ && data_[leftChild] > data_[largestChild] && leftmorethanright) { // leftchild > root
            T tmp = data_[largestChild];
            data_[largestChild] = data_[leftChild];
            data_[leftChild] = tmp;
            i = leftChild;
        }
        else if (rightChild < size_&& data_[rightChild] > data_[largestChild] && !leftmorethanright) { //rightchild > root
            T tmp = data_[largestChild];
            data_[largestChild] = data_[rightChild];
            data_[rightChild] = tmp;
            i = rightChild;
        }
        else if (data_[parent] < data_[largestChild]) { // parent < root
            T tmp = data_[largestChild];
            data_[largestChild] = data_[parent];
            data_[parent] = tmp;
            i = parent;
        }
    }
}

template <typename T>
T& MaxHeap<T>::operator[](int ind) {
    if (ind >= size_) throw "Out of bounds";
    return data_[ind];
}

template <typename T>
T MaxHeap<T>::delEl(int ind) {
    if (ind >= size_) throw "Out of bounds";
    T result = data_[ind];
    data_[ind] = data_[size_ - 1];
    data_[size_ - 1] = 0;
    --size_;
    heapify(ind);
    return result;
}