#include <iostream>
#include <algorithm>
#include <random>
#include <functional>
#include <numeric>
#include <cstdlib>
#include "../HybridSort.hpp"

int main() {
    auto gen = std::bind(std::uniform_int_distribution<>(), std::mt19937());
    const int TEST_CNT = 10;
    for (int i = 0; i < TEST_CNT; i++) {
        const int n = gen() % 20000000 + 1;
        std::vector<int> a(n);
        std::iota(a.begin(), a.end(), 0);
        std::reverse(a.begin(), a.end());
        HybridSort::sort(a.begin(), a.end());
        if (!std::is_sorted(a.begin(), a.end())) {
            std::cout << "test failed" << std::endl;
            exit(0);
        }
    }
    std::cout << "all tests pass" << std::endl;
}