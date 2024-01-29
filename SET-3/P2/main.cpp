#include <iostream>
#include <vector>

constexpr int COUNT_ARRAY_SIZE = 10000000;
constexpr int MAX_ELEMENT = 1000000;

void countingSort(std::vector<int>& A) {
    std::vector<int> v(COUNT_ARRAY_SIZE);
    for (int& i : A) {
        ++v[i + MAX_ELEMENT];
    }
    int cnt = 0;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = v[i]; j != 0; --j) {
            A[cnt] = i - MAX_ELEMENT;
            ++cnt;
        }
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for(int& i : v) {
        std::cin >> i;
    };
    countingSort(v);
    for(int& i : v) {
        std::cout << i << " ";
    }
    return 0;
}
