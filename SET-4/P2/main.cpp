#include <iostream>
#include <vector>
#include <climits>

struct Node {
    int key;
    int left, right;
    bool isBlack;
};

bool isBST(const std::vector<Node> &nodes, int root, int minKey, int maxKey) {
    if (root == -1) {
        return true;
    }
    const Node &node = nodes[root];
    if (node.key <= minKey || node.key >= maxKey) {
        return false;
    }
    return isBST(nodes, node.left, minKey, node.key) && isBST(nodes, node.right, node.key, maxKey);
}

bool isRBTree(const std::vector<Node> &nodes, int root, int blackCount, int &pathBlackCount) {
    if (root == -1) {
        if (pathBlackCount == -1) {
            pathBlackCount = blackCount;
        } else if (pathBlackCount != blackCount) {
            return false;
        }
        return true;
    }

    const Node &node = nodes[root];
    if (!node.isBlack) {
        if ((node.left != -1 || node.right != -1) && !nodes[node.right].isBlack) {
            return false;
        }
    }

    if (node.isBlack) {
        blackCount++;
    }

    return isRBTree(nodes, node.left, blackCount, pathBlackCount) &&
           isRBTree(nodes, node.right, blackCount, pathBlackCount);
}

int main() {
    int n;
    int root;
    std::cin >> n;
    if (n == 0) {
        std::cout << "NO";
        return 0;
    }
    std::cin >> root;
    --root;

    std::vector<Node> nodes(n);
    int number;
    int value;
    std::string left, right;
    char color;
    for (int i = 0; i < n; ++i) {
        std::cin >> number >> value >> left >> right >> color;
        if (left != "null" && right != "null") {
            nodes[number - 1] = {value, std::stoi(left) - 1, std::stoi(right) - 1, color != 'R'};
        } else if (left == "null" && right != "null") {
            nodes[number - 1] = {value, -1, std::stoi(right) - 1, color != 'R'};
        } else if (left != "null" && right == "null") {
            nodes[number - 1] = {value, std::stoi(left) - 1, -1, color != 'R'};
        } else if (left == "null" && right == "null") {
            nodes[number - 1] = {value, -1, -1, color != 'R'};
        }
    }
    if (!nodes[root].isBlack || !isBST(nodes, root, INT_MIN, INT_MAX)) {
        std::cout << "NO";
    } else {
        int pathBlackCount = -1;
        if (!isRBTree(nodes, root, 0, pathBlackCount)) {
            std::cout << "NO";
        } else {
            std::cout << "YES";
        }
    }
    return 0;
}
