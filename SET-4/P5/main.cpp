#include <vector>
#include <algorithm>
#include <iostream>


struct Node {
    int key = 0;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    Node() = default;

    explicit Node(int key) : key(key) {}

    Node(int key, Node *left, Node *right, Node *parent) : key(key), left(left), right(right), parent(parent) {}

    ~Node() {
        delete left;
        delete right;
    }

};

class SplayTree {
public:
    Node *root = nullptr;

    SplayTree() = default;

    ~SplayTree() {
        delete root;
    }

    void insert(int key) {
        if (!root) {
            root = new Node(key);
            return;
        }
        if (root->key == key) {
            return;
        }
        Node *parent = root;
        Node *son = key > root->key ? root->right : root->left;
        while (son) {
            if (son->key < key) {
                son = son->right;
            } else if (son->key > key) {
                son = son->left;
            } else {
                return;
            }
            parent = key > parent->key ? parent->right : parent->left;
        }
        son = new Node(key, nullptr, nullptr, parent);
        if (key > parent->key) {
            parent->right = son;
        } else {
            parent->left = son;
        }
    }

    Node *find(int key) const {
        Node *temp = root;
        while (temp && temp->key != key) {
            temp = key > temp->key ? temp->right : temp->left;
        }
        return temp;
    }

    int splay(Node *node) {
        if (!node || node->key == root->key) {
            return 0;
        }
        size_t count = 0;
        Node *copy = node;
        while (copy->parent) {
            if (copy == copy->parent->left) {
                if (!node->parent->parent) {
                    Left(copy->parent);
                    ++count;
                } else if (copy->parent == copy->parent->parent->left) {
                    Left(copy->parent->parent);
                    Left(copy->parent);
                    ++count;
                    ++count;
                } else {
                    Left(copy->parent);
                    Right(copy->parent);
                    ++count;
                }
            } else {
                if (!copy->parent->parent) {
                    Right(copy->parent);
                    ++count;
                } else if (copy->parent == copy->parent->parent->right) {
                    Right(copy->parent->parent);
                    Right(copy->parent);
                    ++count;
                    ++count;
                } else {
                    Right(copy->parent);
                    Left(copy->parent);
                    ++count;
                }
            }
        }
        root = copy;
        return count;
    }

    int getHeight() const {
        if (root) {
            return _getHeight(root);
        }
        return 0;
    }

private:
    int _getHeight(Node *node) const {
        if (node) {
            return std::max(_getHeight(node->left), _getHeight(node->right)) + 1;
        }
        return -1;
    }

    static void Right(Node *node) {
        Node *right = node->right;
        node->right = right->left;
        if (node->right) {
            node->right->parent = node;
        }
        right->parent = node->parent;
        if (node->parent) {
            if (node == node->parent->left) {
                node->parent->left = right;
            } else {
                node->parent->right = right;
            }
        }
        right->left = node;
        node->parent = right;
    }

    static void Left(Node *node) {
        Node *left = node->left;
        node->left = left->right;
        if (node->left) {
            node->left->parent = node;
        }
        left->parent = node->parent;
        if (node->parent) {
            if (node == node->parent->left) {
                node->parent->left = left;
            } else {
                node->parent->right = left;
            }
        }
        left->right = node;
        node->parent = left;
    }
};
