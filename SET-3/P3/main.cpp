#include <iostream>
#include <vector>


void countingSort(std::vector<int>& A, int k) {
    std::vector<std::vector<int>> v(19, std::vector<int>());
    int m = 1;
    for (int i = k; i > 0; --i) {
        m *= 10;
    }
    for (int& i : A) {
        int j = i % m / (m / 10);
        v[j + 9].push_back(i);
    }
    int cnt = 0;
    for (int i = 0; i < v.size(); ++i) {
        for (int l = 0; l != v[i].size(); ++l) {
            A[cnt] = v[i][l];
            ++cnt;
        }
    }
}

void radixSort(std::vector<int>& A) {
    for(int i = 1; i < 10; ++i){
        countingSort(A, i);
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
    radixSort(v);
    for(int& i : v) {
        std::cout << i << " ";
    }
    return 0;
}
