#include <iostream>
#include <algorithm>

struct Node {
    int value;
    Node* left;
    Node* right;
    int height;

    Node(int value) : value(value), left(nullptr), right(nullptr), height(1) {}
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRec(root, value);
    }

    bool isAVLBalanced() {
        return check(root) != -1;
    }

private:
    Node* insertRec(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->value) {
            node->left = insertRec(node->left, value);
        }
        else if (value > node->value) {
            node->right = insertRec(node->right, value);
        }
        node->height = 1 + std::max(height(node->left), height(node->right));
        return node;
    }

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int check(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = check(node->left);
        int rightHeight = check(node->right);
        if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        return 1 + std::max(leftHeight, rightHeight);
    }
};

int main() {
    BinaryTree tree;
    int value;
    while (std::cin >> value && value != 0) {
        tree.insert(value);
    }
    std::cout << (tree.isAVLBalanced() ? "YES" : "NO") << std::endl;
    return 0;
}
