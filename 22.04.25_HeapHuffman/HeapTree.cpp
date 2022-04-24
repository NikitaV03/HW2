#include <iostream>
#include "Arr.h"
#include "MaxHeap.h"
#include <string>

template<typename T> 
class PriorQueue {
    MaxHeap<T> data_;
    int size_;
public:
    PriorQueue() : data_(), size_(0) {}
    PriorQueue(T* data, int size) {
        for (int i = 0; i < size; ++i) {
            data_.add(data[i]);
        }
    }
    T getFirst() {
        --size_;
        if (size_ >= 0) return data_.delEl(0);
        return 0;
    }
    T& getElem(int ind) {
        return data_[ind];
    }
    void add(const T& x) {
        data_.add(x);
        ++size_;
    }
    const int getSize() const { return size_; }
};

struct Node {
    int freq; 
    char symb;
    Node(int a = 0): freq(0), symb(0) {}
    Node(int a, char s): freq(a), symb(s) {}
    Node(const Node& X) {
        freq = X.freq;
        symb = X.symb;
    }
    //~node
    Node& operator[](int ind) { return *this; }
    bool operator<(const Node& a) { return freq < a.freq; }
    bool operator>(const Node& a) { return freq > a.freq; }
    bool operator==(const Node& a) { return freq == a.freq; }
    bool operator!=(const Node& a) { return freq != a.freq; }
    Node& operator=(const Node& X) {
        if (this != &X) {
            freq = X.freq;
            symb = X.symb;
        }
        return *this;
    }
    Node& operator=(Node&& X) {
        if (this != &X) {
            freq = X.freq;
            symb = X.symb;
            X.freq = 0;
            X.symb = 0;
        }
        return *this;
    }
};

std::ostream& operator<<(std::ostream& out, const Node& node) {
    out << node.freq << node.symb;
    return out;
}

int main()
{

    PriorQueue<Node> Symbols;
    Node c = 0;
    std::string toread = "aaabbbcccddccc";
    std::string bigtoread = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
        "Nullam vel quam volutpat libero placerat tincidunt id ut risus. "
        "Nulla facilisi. Duis ut libero tristique, aliquam lacus id, commodo justo. "
        "Nunc cursus vehicula odio, quis pretium risus venenatis et. In vel consequat enim. "
        "Curabitur vitae elit egestas, dapibus mi non, auctor magna. Nullam dignissim quis elit at elementum.";
    unsigned int arrchar[256] = {};
    for (int i = 0; i < bigtoread.size(); ++i) {
        ++arrchar[bigtoread[i]];
    }
    for (int i = 0; i < 256; ++i) {
        if (arrchar[i] != 0) {
            Node tmp(arrchar[i], i);
            Symbols.add(tmp);
        }
    }
    int size = Symbols.getSize();
    for (int i = 0; i < size; ++i) {
        std::cout << Symbols.getElem(i) << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << Symbols.getFirst() << " ";
    }
    std::cout << std::endl;
}