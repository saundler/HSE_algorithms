#include <vector>

struct Node {
    Node* next;
    Node* previous;
    int data;

    Node();
    Node(int valiue);
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other);
    explicit DoublyLinkedList(std::vector<int>& array);
    ~DoublyLinkedList();

    void pushBack(int data);
    void pushFront(int data);
    void insert(Node* prev, int data);
    void popFront();
    void popBack();
    void pop(Node* pos);
    void erase();
    void reverse();
    void removeDuplicates();
    void replace(int oldElem, int newElem);
};