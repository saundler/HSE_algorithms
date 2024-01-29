#include <set>
#include <vector>
#include <iostream>

struct Node {
    Node *next;
    Node *previous;
    int data;

    Node() : next(nullptr), previous(nullptr), data(0) {}

    Node(int valiue) : next(nullptr), previous(nullptr), data(valiue) {}
};

class DoublyLinkedList {
public:
    Node *head;
    Node *tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    DoublyLinkedList(const DoublyLinkedList &other) : DoublyLinkedList() {
        for (Node *tmp = other.head; tmp != nullptr; tmp = tmp->next) {
            pushBack(tmp->data);
        }
    }

    DoublyLinkedList(std::vector<int> &array) : DoublyLinkedList() {
        for (const int i: array) {
            pushBack(i);
        }
    }

    ~DoublyLinkedList() {
        erase();
    }

    void pushBack(int data) {
        if (!head) {
            head = new Node(data);
            tail = head;
        } else {
            tail->next = new Node(data);
            tail->next->previous = tail;
            tail = tail->next;
        }
    }

    void pushFront(int data) {
        if (!head) {
            pushBack(data);
        } else {
            head->previous = new Node(data);
            head->previous->next = head;
            head = head->previous;
        }
    }

    void insert(Node *prev, int data) {
        if (!prev || !contains(prev)) {
            throw std::runtime_error("Wrong position for insertion!");
        }
        Node *next = prev->next;
        prev->next = new Node(data);
        prev->next->next = next;
        prev->next->previous = prev;
        if (next) {
            next->previous = prev->next;
        }
    }

    void popFront() {
        if (!head) {
            throw std::runtime_error("Deletion error!");
        }
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            delete head->previous;
            head->previous = nullptr;
        }

    }

    void popBack() {
        if (!head) {
            throw std::runtime_error("Deletion error!");
        }
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->previous;
            delete tail->next;
            tail->next = nullptr;
        }
    }

    void pop(Node *pos) {
        if (!pos || !contains(pos)) {
            throw std::runtime_error("Deletion error!");
        }
        if (head == tail) {
            delete pos;
            head = nullptr;
            tail = nullptr;
        } else {
            if (pos == head) {
                head = head->next;
            } else {
                pos->previous->next = pos->next;
            }
            if (pos == tail) {
                tail = tail->previous;
            } else {
                pos->next->previous = pos->previous;
            }
            delete pos;
        }
    }

    void erase() {
        while (tail) {
            popBack();
        }
    }

    void reverse() {
        Node *next;
        for (Node *tmp = head; tmp != nullptr; tmp = next) {
            next = tmp->next;
            tmp->next = tmp->previous;
            tmp->previous = next;
        }
        next = head;
        head = tail;
        tail = next;
    }

    void removeDuplicates() {
        std::set<int> array;
        for (Node *tmp = head; tmp != nullptr; tmp = tmp->next) {
            if (array.find(tmp->data) == array.end()) {
                array.insert(tmp->data);
            } else {
                pop(tmp);
            }
        }
    }

    void replace(int oldElem, int newElem) {
        for (Node *tmp = head; tmp != nullptr; tmp = tmp->next) {
            if (tmp->data == oldElem) {
                tmp->data = newElem;
            }
        }
    }

private:
    bool contains(Node* pos) {
        for (Node *tmp = head; tmp != nullptr; tmp = tmp->next) {
            if (pos == tmp) {
                return true;
            }
        }
        return false;
    }
};