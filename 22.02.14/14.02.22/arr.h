#pragma once
#include <iostream>


template<typename T>
class Arr
{
private:
    T* storage;
    size_t size;
public:
    Arr(T* store = nullptr, int sz = 0) : storage(store), size(sz) {
        std::cout << "hello, guys" << std::endl;
    }
    /*Arr(){
        size = 0;
        storage = nullptr;
    }
    */
    Arr(const Arr& X) : storage(X.storage), size(X.size) {
        std::cout << "copied" << std::endl;
    }
    ~Arr() {
        std::cout << "bye, guys" << std::endl;
    }


    bool iseverythingok() {
        //all is ok, i swear
        std::cout << "test passed" << std::endl;
        return 1;
    }

    void printAll() const {
        std::cout << " arr: ";
        int size = getsize();
        for (size_t i = 0; i < size; ++i) {
            std::cout << getelem(i) << " ";
        }
        std::cout << std::endl << "Size: " << size << std::endl;
    }

    T getelem(size_t ind) const{
        if (ind < size) {
            return storage[ind];
        }
        else {
            std::cout << " try another index" << std::endl;
            return -1;
        }
    }
    int getsize() const {
        return size;
    };
    void resize(size_t new_size) {
        T* storg = new T[new_size];
        if (new_size >= size) {
            for (int i = 0; i < size; i++) {
                storg[i] = storage[i];
            }
        }
        else {
            for (int i = 0; i < new_size; i++) {
                storg[i] = storage[i];
            }
        }
        delete[] storage;
        storage = storg;
        size = new_size;
    }
    void initWith(int elems, ...) {
        for (int* ptr = &elems; elems > 0; elems--)
        {
            storage[elems - 1] = *(++ptr);
        }
    }
    T& removeelem(size_t ind) {
        T* storg = new T[size - 1];
        if (ind < size) {
            for (size_t i = 0; i < ind; ++i) {
                storg[i] = storage[i];
            }
            for (size_t i = ind + 1; i < size; ++i) {
                storg[i - 1] = storage[i];
            }
        }
        int elem = storage[ind];
        delete[] storage;
        storage = storg;
        --size;
        return elem;
    }

    void addElem(T elem) {
        T* storg = new T[size + 1];
        for (size_t i = 0; i < size; ++i) {
            storg[i] = storage[i];
        }
        storg[size] = elem;
        delete[] storage;
        storage = storg;
        ++size;
    }
};