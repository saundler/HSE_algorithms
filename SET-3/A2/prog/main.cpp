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

void insertionSort(std::vector<int>& array) {
    for (int i = 1; i < array.size(); ++i) {
        int key = array [i];
        int j = i - 1;
        for (; j > 0 && array[j] > key; --j) {
            array[j + 1] = array[j];
        }
        array[j + 1] = key;
    }
}

void merge(std::vector<int>& array, int const left, int const mid, int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;
    std::vector<int> leftArray(subArrayOne);
    std::vector<int> rightArray(subArrayTwo);
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;
    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                    = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                    = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeInsertionSort(std::vector<int>& array, int const begin, int const end, int insertionLength)
{
    if (begin >= end)
        return;
    if (array.size() <= insertionLength) {
        insertionSort(array);
        return;
    }
    int mid = begin + (end - begin) / 2;
    mergeInsertionSort(array, begin, mid, insertionLength);
    mergeInsertionSort(array, mid + 1, end, insertionLength);
    merge(array, begin, mid, end);
}

int main() {
    for (int i = 100; i <= 5000; i += 100) {
        //std::vector<int> array = generateRandomArray(i, 0 , 3000);
        //std::vector<int> array = generateReverseArray(i);
        std::vector<int> array = generatAlmostSortedArray(i);
        auto start = std::chrono::high_resolution_clock::now();
        mergeInsertionSort(array, 0, i, 50);
        auto end = std::chrono::high_resolution_clock::now();
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout /*<< i << " : "*/<< microseconds << std::endl;
    }

    return 0;
}
