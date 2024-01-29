#include <initializer_list>
#include <iostream>

enum class Color { RED, BLACK };

template <typename T>
class Node {
public:
    T key;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    Color color;

    Node(T value) : key(value), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {}
};

template <typename T>
class RBTree {
public:
    Node<T>* root;

    RBTree() : root(nullptr) {}

    RBTree(std::initializer_list<T> values) : root(nullptr) {
        for (const T& value : values) {
            insert(value);
        }
    }

    ~RBTree() {
        destroyTree(root);
    }

    void insert(T key) {
        Node<T>* newNode = new Node<T>(key);
        Node<T>* y = nullptr;
        Node<T>* x = this->root;

        while (x != nullptr) {
            y = x;
            if (newNode->key < x->key) {
                x = x->left;
            } else if (newNode->key > x->key) {
                x = x->right;
            } else {
                delete newNode;
                return;
            }
        }

        newNode->parent = y;
        if (y == nullptr) {
            this->root = newNode;
        } else if (newNode->key < y->key) {
            y->left = newNode;
        } else {
            y->right = newNode;
        }

        if (newNode->parent == nullptr){
            newNode->color = Color::BLACK;
            return;
        }

        if (newNode->parent->parent == nullptr) {
            return;
        }

        fixInsert(newNode);
    }

    T* find(const T& key) const {
        Node<T>* result = findNode(root, key);
        return (result != nullptr) ? &(result->key) : nullptr;
    }

    size_t size() const {
        return countNodes(root);
    }

    T* lowerBound(const T& value) const {
        Node<T>* result = lowerBoundNode(root, value);
        return (result != nullptr) ? &(result->key) : nullptr;
    }

    bool empty() const {
        return root == nullptr;
    }

private:
    void fixInsert(Node<T>* k) {
        Node<T>* u;
        while (k != root && k->parent->color == Color::RED) {
            if (k->parent == k->parent->parent->left) {
                u = k->parent->parent->right;
                if (u && u->color == Color::RED) {
                    u->color = Color::BLACK;
                    k->parent->color = Color::BLACK;
                    k->parent->parent->color = Color::RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        rotateLeft(k);
                    }
                    k->parent->color = Color::BLACK;
                    if(k->parent->parent) {
                        k->parent->parent->color = Color::RED;
                        rotateRight(k->parent->parent);
                    }
                }
            } else {
                u = k->parent->parent->left;
                if (u && u->color == Color::RED) {
                    u->color = Color::BLACK;
                    k->parent->color = Color::BLACK;
                    k->parent->parent->color = Color::RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rotateRight(k);
                    }
                    k->parent->color = Color::BLACK;
                    if(k->parent->parent) {
                        k->parent->parent->color = Color::RED;
                        rotateLeft(k->parent->parent);
                    }
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = Color::BLACK;
    }
    Node<T>* findNode(Node<T>* current, const T& key) const {
        while (current != nullptr) {
            if (key == current->key) {
                return current;
            } else if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    }
    size_t countNodes(Node<T>* current) const {
        if (current == nullptr) {
            return 0;
        }
        return 1 + countNodes(current->left) + countNodes(current->right);
    }

    Node<T>* lowerBoundNode(Node<T>* current, const T& value) const {
        Node<T>* result = nullptr;
        while (current != nullptr) {
            if (current->key >= value) {
                result = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return result;
    }

    void destroyTree(Node<T>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void rotateLeft(Node<T>* x) {
        Node<T>* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node<T>* y) {
        Node<T>* x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }
};