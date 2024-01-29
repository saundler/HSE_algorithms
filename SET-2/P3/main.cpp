#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <limits>
#include <cstdint>

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

static int64_t Distance(std::vector<Point>::iterator first, std::vector<Point>::iterator second) {
    return (int64_t) std::sqrt(std::pow(first->x - second->x, 2) + std::pow(first->y - second->y, 2));
}

std::vector<Point> tmp;

int64_t Find_Min_Distance(std::vector<Point>::iterator begin, std::vector<Point>::iterator end) {
    int64_t size = std::distance(begin, end);
    if (size == 1) {
        return std::numeric_limits<int64_t>::max();
    }
    if (size == 2) {
        return Distance(begin, begin + 1);
    }
    auto middle = begin + size / 2;
    int64_t min_distance = std::min(Find_Min_Distance(begin, middle), Find_Min_Distance(middle, end));
    auto left_begin = middle - 1;
    while ((left_begin - 1) >= begin && middle->x - (left_begin - 1)->x <= min_distance) {
        --left_begin;
    }
    tmp.clear();
    for (auto i = middle; i < end && i->x - middle->x <= min_distance; ++i) {
        tmp.push_back(*i);
    }
    std::sort(tmp.begin(), tmp.end(),[](Point& a, Point& b){ return std::tie(a.y, a.x) < std::tie(b.y, b.x); });
    for (auto i = left_begin; i < middle; ++i) {
        for (auto j = tmp.begin(); j < tmp.end() && (j->y - i->y) <= min_distance; ++j) {
            if (std::abs(i->y - j->y) > min_distance || (j != tmp.begin() && (j - 1)->y == j->y)) {
                continue;
            }
            int64_t current_distance = Distance(i, j);
            if (current_distance < min_distance) {
                min_distance = current_distance;
            }
        }
    }
    return min_distance;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<Point> points;
    int x, y;
    while (std::cin >> x >> y) {
        points.emplace_back(x, y);
    }
    std::sort(points.begin(), points.end(), [](Point &a, Point &b) { return std::tie(a.x, a.y) < std::tie(b.x, b.y); });
    std::cout << (int64_t) Find_Min_Distance(points.begin(), points.end());
    return 0;
}
