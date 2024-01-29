#include <iostream>
#include <iterator>
#include <cstdint>
#include <vector>

class Node {
public:
    Node *parent;
    int64_t size;
    std::vector<int64_t> data;
    std::vector<Node *> ptrs;

    Node(int64_t size, Node *parent) : parent(parent), size(size), data(std::vector<int64_t>()),
                                   ptrs(std::vector<Node *>()) {}

    void add(int value, Node *left, Node *rigth) {
        int64_t pos = 0;
        if (data.size() >= size) {
            pos = size / 2;
            Node *l = new Node(size, this);
            Node *r = new Node(size, this);
            for (int i = 0; i < pos; ++i) {
                l->data.push_back(data[i]);
                l->ptrs.push_back(ptrs[i]);
            }
            l->ptrs.push_back(ptrs[pos]);
            for (int i = pos + 1; i < data.size(); ++i) {
                r->data.push_back(data[i]);
                r->ptrs.push_back(ptrs[i]);
            }
            r->ptrs.push_back(ptrs[pos + 1]);
            if (value < data[pos]) {
                l->add(value, left, rigth);
            } else {
                r->add(value, left, rigth);
            }
            if (parent) {
                l->parent = parent;
                r->parent = parent;
                parent->add(data[pos], l, r);
                delete this;
            } else {
                int64_t tmp = data[pos];
                data.clear();
                ptrs.clear();
                data.push_back(tmp);
                ptrs.push_back(l);
                ptrs.push_back(r);
            }
            return;
        }
        for (; pos < data.size() && value > data[pos]; ++pos) {}
        data.insert(data.begin() + pos, value);
        if (data.size() == ptrs.size()) {
            ptrs[pos] = left;
            ptrs.insert(ptrs.begin() + pos + 1, rigth);
        } else {
            ptrs.insert(ptrs.begin() + pos, left);
            ptrs.insert(ptrs.begin() + pos + 1, rigth);
        }
    }

    [[nodiscard]] size_t childCount() const {
        size_t tmp = 0;
        for (auto i: ptrs) {
            if (i) {
                tmp += i->childCount() + 1;
            }
        }
        return tmp;
    }

    int64_t count() const {
        int64_t tmp = 0;
        bool flag = false;
        for (auto i: ptrs) {
            if (i) {
                flag = true;
                tmp += i->count();
            }
        }
        if (!flag) {
            for (auto i: data) {
                tmp += i;
            }
        }
        return tmp;
    }

    ~Node() {
        for (Node *ptr: ptrs) {
            delete ptr;
        }
    }
};

class BTree {
public:
    explicit BTree(int nodeSize) : nodeSize(nodeSize), root(nullptr) {}

    ~BTree() {
        delete root;
    }

    void insert(int64_t value) {
        if (!root) {
            root = new Node(nodeSize, nullptr);
            root->add(value, nullptr, nullptr);
            return;
        }
        Node *node = find(value, root);
        if (node) {
            node->add(value, nullptr, nullptr);
        }
    }

    Node *find(int64_t value, Node *tmp) {
        for (int64_t i = 0; i <= tmp->data.size(); ++i) {
            if (tmp->data.size() && ((i == 0 && value < tmp->data[i]) || (i == tmp->data.size() && value > tmp->data[i - 1]) || (i != 0 && i != tmp->data.size() && tmp->data[i - 1] < value && value < tmp->data[i]))) {
                if (tmp->ptrs[i]) {
                    return find(value, tmp->ptrs[i]);
                }
                return tmp;
            }
        }
        return nullptr;
    }

    [[nodiscard]] size_t size() const {
        return root->childCount() + 1;
    }

    int64_t sum() const {
        return root->count();
    }


    int nodeSize;
    Node *root;
};

int main() {
    BTree a(3);
    std::vector<int64_t> numbers = {
            634294765, 202328112, 622515008, 860196613, 465456895,
            168536124, 197306915, 919723586, 206855444, 907674999,
            39831811, 523952770, 203217864, 599687494, 367226838,
            8887557, 514152596, 665229562, 181976349, 314834181,
            96310114, 304428905, 61782982, 975852366, 707762482,
            19472122, 321498202, 935515003, 331015035, 861582359,
            282832949, 232300400, 517844955, 419831106, 772832671,
            760996787, 333709612, 783344644, 920354588, 26612159,
            873492299, 373313814, 112281191, 238022020, 92372521,
            285649202, 934063165, 773775392, 655071949, 307159054
    };
    for(auto i : numbers) {
        a.insert(i);
    }
    for (auto i: a.root->data) {
        std::cout << i << std::endl;
    }
    std::cout << a.size() << " " << a.sum() << std::endl;
}