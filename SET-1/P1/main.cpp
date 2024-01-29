#include "DoublyLinkedList.cpp"
#include "iostream"

int main() {
    std::vector<int> v({});
    DoublyLinkedList a(v);
    a.reverse();
    for (Node* c = a.head; c != nullptr; c = c->next) {
        std::cout <<  c->data << "\n";
    }
    return 0;
}
