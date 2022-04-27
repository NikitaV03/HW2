#pragma once
#include <utility>

template <typename T>
class Arr {
    T* data_;
    unsigned int size_;
    unsigned int max_size_;
    bool isSorted_;
public:
    Arr(unsigned int n = 0) : size_(0), max_size_(n), data_(nullptr), isSorted_(true) {
        if (max_size_ > 0) {
            data_ = new T[max_size_];
            if (!data_) throw "Out of memory";
        }
    }
    Arr(const Arr& A) {
        isSorted_ = A.isSorted_;
        size_ = A.size_;
        max_size_ = A.max_size_;
        data_ = new T[max_size_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = A.data_[i];
        }
    }
    Arr(Arr&& A) {
        data_ = A.data_;
        size_ = A.size_;
        max_size_ = A.max_size_;
        isSorted_ = A.isSorted_;
        A.data_ = 0;
        A.size_ = 0;
        A.max_size_ = 0;
    }
    ~Arr() {
        clear();
    }
    Arr& operator=(const Arr& A);
    Arr& operator=(Arr&& A);

    unsigned int size() const { return size_; }
    unsigned int capacity() const { return max_size_; }
    void push_back(const T& x);
    T& operator[](unsigned int i) const {
        if (i >= size_) throw "Out of bounds";
        return data_[i];
    }

    void empty() { size_ = 0; }
    void clear() {
        if (data_) {
            delete[] data_;
            size_ = 0;
            max_size_ = 0;
            data_ = nullptr;
        }
    }

    class iterator {
        T* current_;
    public:
        iterator(T* pos = nullptr) : current_(pos) {}
        T& operator*() const { return *current_; }
        T& operator*() { return *current_; }
        bool operator==(const iterator& pos) const { return current_ == pos.current_; }
        bool operator!=(const iterator& pos) const { return current_ != pos.current_; }
        iterator& operator++() {
            ++current_;
            return *this;
        }
        iterator operator++(int) {
            T* tmp = current_;
            ++current_;
            return iterator(tmp);
        }
        friend class Arr;
    };
    iterator begin() const { return iterator(data_); }
    iterator end() const { return iterator(data_ + size_); }


    class reverse_iterator {
        T* current_;
    public:
        reverse_iterator(T* pos = nullptr) : current_(pos) {}
        T& operator*() const { return *current_; }
        T& operator*() { return *current_; }
        bool operator==(const reverse_iterator& pos) const { return current_ == pos.current_; }
        bool operator!=(const reverse_iterator& pos) const { return current_ != pos.current_; }
        reverse_iterator& operator++() {
            --current_;
            return *this;
        }
        reverse_iterator operator++(int) {
            T* tmp = current_;
            --current_;
            return iterator(tmp);
        }
        friend class Arr;
    };
    reverse_iterator rbegin() const { return reverse_iterator(data_ + size_ - 1); }
    reverse_iterator rend() const { return reverse_iterator(data_ - 1); }

    void sort() {
        //quicksort
        int len = size_;
        int stacksize = 0;
        while (len > 0) {
            len /= 2;
            ++stacksize;
        }
        int* LeftStack = new int[stacksize];
        int* RightStack = new int[stacksize];
        int topElement = 0;
        LeftStack[topElement] = 0;
        RightStack[topElement] = size_ - 1;

        while (topElement > -1) {
            int left = LeftStack[topElement];
            int right = RightStack[topElement];
            --topElement;
            int i = left, j = right;
            int pindex = i + (j - i) / 2;
            T p = data_[pindex];
            while (i < j) {
                while (data_[i] < p) ++i;
                while (p < data_[j]) --j;
                if (i < j) {
                    std::swap(data_[i], data_[j]);
                    ++i; --j;
                }
                else if (i == j) {
                    ++i; --j;
                }
            }
            if (pindex < i) { // правая часть меньше, чем левая
                if (j > left) { ++topElement; LeftStack[topElement] = left; RightStack[topElement] = j;}
                if (i < right) { ++topElement; LeftStack[topElement] = i; RightStack[topElement] = right;}
            }
            else {
                if (i < right) { ++topElement; LeftStack[topElement] = i; RightStack[topElement] = right; }
                if (j > left) { ++topElement; LeftStack[topElement] = left; RightStack[topElement] = j; }
            }
        }
        delete[] LeftStack;
        delete[] RightStack;
        isSorted_ = true;
    }
    iterator find(const T&) const;
    void erase(const iterator&);
};

template <typename T>
Arr<T>& Arr<T>::operator=(const Arr<T>& A) {
    if (this != &A) {
        if (data_) delete data_;
        isSorted_ = A.isSorted_;
        size_ = A.size_;
        max_size_ = A.max_size_;
        data_ = new T[max_size_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = A.data_[i];
        }
    }
    return *this;
}

template <typename T>
Arr<T>& Arr<T>::operator=(Arr<T>&& A) {
    if (this != &A) {
        if (data_) delete data_;
        size_ = A.size_;
        max_size_ = A.max_size_;
        data_ = A.data_;
        isSorted_ = A.isSorted_;
        A.data_ = nullptr;
        A.size_ = 0;
        A.max_size_ = 0;
    }
    return *this;
}

template <typename T>
void Arr<T>::push_back(const T& x) {
    if (size_ + 1 > max_size_) { // max_size * 2.
        unsigned int newsize = max_size_ < 1 ? (max_size_ + 1) : 2 * max_size_;
        T* tmp = new T[newsize];
        if (!tmp) throw "Out of memory";
        for (unsigned int i = 0; i < max_size_; ++i)
            tmp[i] = data_[i];
            //tmp[i] = std::move(data_[i]);
        //delete[] data_;
        data_ = tmp;
        max_size_ = newsize;
    }
    data_[size_] = x;
    ++size_;
    isSorted_ = false;
}

template <typename T>
typename Arr<T>::iterator Arr<T>::find(const T& X) const {
    if (isSorted_) { //binsearch
        unsigned int left = 0, right = size_ - 1;
        while (left < right) {
            unsigned int p = left + (right - left) / 2;
            if (data_[p] < X) left = p + 1;
            else if (data_[p] == X)
                return iterator(data_ + p);
            else if (p == 0) break;
            else right = p - 1;
        }
        if (data_[left] == X) return iterator(data_ + left);
    }
    else {
        for (unsigned int i = 0; i < size_; ++i)
            if (data_[i] == X) return iterator(data_ + i);
    }
    return end();
}

template <typename T>
void Arr<T>::erase(typename const Arr<T>::iterator& pos) {
    if (pos == end()) return;
    T* cur = pos.current_;
    while (cur != (data_ + size_ - 1)) {
        *cur = std::move(*(cur + 1));
        ++cur;
    }
    --size_;
}