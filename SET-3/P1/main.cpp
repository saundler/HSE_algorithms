#include <iostream>
#include <vector>
#include <algorithm>

void heapify(std::vector<int> &A, int n, int i) {
    int l = 2 * i + 1, r = 2 * i + 2;
    int largest = i;
    if (l < n && A[l] > A[largest]) {
        largest = l;
    }
    if (r < n && A[r] > A[largest]) {
        largest = r;
    }
    if (largest != i) {
        std::swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

void buildHeap(std::vector<int> &A) {
    for (int i = A.size() / 2 - 1; i >= 0; --i) {
        heapify(A, A.size(), i);
    }
}

void heapSort(std::vector<int> &A) {
    buildHeap(A);
    for (int i = A.size() - 1; i >= 0; --i) {
        std::swap(A[i], A[0]);
        heapify(A, i, 0);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> heap(n);
    for (int &i: heap) {
        std::cin >> i;
    }
    heapSort(heap);
    for (int &i: heap) {
        std::cout << i << " ";
    }
    return 0;
}
