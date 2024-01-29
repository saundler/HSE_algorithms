#include <iostream>
#include <vector>
#include <chrono>
#include <random>

std::vector<int> generateRandomArray(int size, int from, int to) {
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rnd(seed);
    std::uniform_int_distribution<int> rand(from, to);
    std::vector<int> randomArray(size);
    for (int i = 0; i < size; ++i) {
        randomArray[i] = rand(rnd);
    }
    return randomArray;
}

std::vector<int> generateReverseArray(int size) {
    std::vector<int> reverseArray(size);
    for (int i = size - 1; i >= 0; --i) {
        reverseArray[size - 1 - i] = i;
    }
    return  reverseArray;
}

std::vector<int> generatAlmostSortedArray(int size) {
    std::vector<int> almostSortedArray(size);
    for (int i = 0; i < size; ++i) {
        almostSortedArray[i] = i;
        if (i % 199 == 0) {
            std::swap(almostSortedArray[i], almostSortedArray[i - 100]);
        }
    }
    return  almostSortedArray;
}

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickHeapSort(std::vector<int>& arr, int low, int high, int threshold) {
    if (low < high) {
        if (high - low < threshold) {
            heapSort(arr, high - low + 1);
        } else {
            int pi = partition(arr, low, high);
            quickHeapSort(arr, low, pi - 1, threshold);
            quickHeapSort(arr, pi + 1, high, threshold);
        }
    }
}

int main() {
    for (int i = 100; i <= 5000; i += 100) {
        //std::vector<int> array = generateRandomArray(i, 0 , 3000);
        //std::vector<int> array = generateReverseArray(i);
        std::vector<int> array = generatAlmostSortedArray(i);
        auto start = std::chrono::high_resolution_clock::now();
        quickHeapSort(array, 0, i, 50);
        auto end = std::chrono::high_resolution_clock::now();
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout /*<< i << " : "*/<< microseconds << std::endl;
    }
    return 0;
}
