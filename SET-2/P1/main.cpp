#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdint>

struct Interval {
    int left;
    int right;

    Interval() : left(1), right(0) {}

    Interval(int left, int right) : left(left), right(right) {}

    int64_t length() {
        return (int64_t) right - left + 1;
    }

    Interval overlap(const Interval &other) const {
        if (right < other.left || left > other.right) {
            return Interval(1, 0);
        }
        return Interval(std::max(left, other.left), std::min(right, other.right));
    }

    bool operator<(const Interval &other) const {
        return left == other.left ? right < other.right : left < other.left;
    }
    bool operator<=(const Interval &other) const {
        return (left == other.left && right == other.right) || *this < other;
    }
};

void merge(std::vector<Interval>& array, int const left, int const mid, int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;
    std::vector<Interval> leftArray(subArrayOne);
    std::vector<Interval> rightArray(subArrayTwo);
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

void mergeSort(std::vector<Interval>& array, int const begin, int const end)
{
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

int main() {
    size_t n;
    std::cin >> n;
    if (n == 0){
        std::cout << 0;
        return 0;
    }
    std::vector<Interval> intervals;
    intervals.reserve(n);
    int left, right;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> left >> right;
        intervals.emplace_back(left, right);
    }
    mergeSort(intervals, 0, intervals.size() - 1);
    Interval first = intervals.front();
    Interval temp(1, 0);
    Interval biggest(1, 0);
    for (int i = 1; i < intervals.size(); ++i) {
        temp = first.overlap(intervals[i]);
        if (temp.length() > biggest.length()) {
            biggest = temp;
        }
        first = first.right < intervals[i].right ? intervals[i] : first;
    }
    std::cout << biggest.length() << "\n";
    if (biggest.length()){
        std::cout << biggest.left << " " << biggest.right;
    }
    return 0;
}