#include <algorithm>
#include <vector>
#include <iostream>

size_t HammingDistance(std::vector<int> &array, std::vector<int> &new_array) {
    size_t distance = 0;
    for (size_t i = 0; i < array.size(); ++i) {
        if (array[i] != new_array[i]) {
            ++distance;
        }
    }
    return distance;
}

size_t CountArrayRotations(std::vector<int> &array) {
    size_t n = array.size();
    size_t count = 0;
    std::vector<std::vector<int>> arrays;
    std::vector<size_t> distances;
    for (size_t i = 0; i < n; ++i) {
        std::vector<int> new_array(n);
        for (size_t j = n - i, cnt = 0; j < n; ++j, ++cnt) {
            new_array[cnt] = array[j];
        }
        for (size_t j = i, cnt = 0; j < n; ++j, ++cnt) {
            new_array[j] = array[cnt];
        }
        if (std::find(arrays.begin(), arrays.end(), new_array) == arrays.end()) {
            arrays.push_back(new_array);
        }
    }
    for (auto i : arrays) {
        distances.push_back(HammingDistance(array, i));
    }
    size_t maxvalue = *std::max_element(distances.begin(), distances.end());
    for (size_t i: distances) {
        if (maxvalue == i) {
            ++count;
        }
    }
    return count;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t size;
    std::cin >> size;
    std::vector<int> array(size);
    for (size_t i = 0; i < size; ++i) {
        std::cin >> array[i];
    }

    std::cout << CountArrayRotations(array);
    return 0;
}