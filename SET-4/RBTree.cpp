#include <iostream>
#include <cstdio>

enum class Color { RED, BLACK };

template <typename T>
struct Node {
    T key;
    Node *left;
    Node *right;
    Node *parent;
    Color color;
    
    Node();
};

template <typename T>
class RBTree {
public:
    RBTree();
    RBTree(std::initializer_list<T> list);
    ~RBTree();

    void insert(T key);
    
    int size() const;

    bool empty() const;

    T *lowerBound(T key) const;

    T *find(T key) const;

    Node<T> *root{};
};
