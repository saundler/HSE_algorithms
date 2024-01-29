#include <random>
#include <iostream>

std::pair<double, double> randomPoint() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(-1, 1);
    return std::make_pair(distrib(gen), distrib(gen));
}

bool locatedInCircle(const std::pair<double, double>& point) {
    return point.first * point.first + point.second * point.second <= 1;
}

int main() {
    int points_num;
    std::cout << "Enter the number of points:";
    std::cin >> points_num;
    if(!points_num){
        std::cout << "Insufficient number of points!!!";
        return 0;
    }
    int m = 0;
    for (int i = 0 ; i < points_num; ++i){
        if(locatedInCircle(randomPoint())) {
            ++m;
        }
    }
    std::cout << "The value of Pi is equal to: " << 4 * m / (double)points_num;
    return 0;
}
