#include "benchmark.h"
#include "../HybridSort.hpp"
#include <ctime>
#include <iostream>
#include <functional>
#include <vector>
#include <random>
#include <string>

static void hybridSort(benchmark::State &state) {
    const int n = state.range(0);
    auto gen = std::bind(std::uniform_int_distribution<int>(), std::mt19937());
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = gen();
    std::sort(a.begin(), a.end());
    std::vector<int> b;
    for (auto s : state) {
        b = a;
        HybridSort::sort(b.begin(), b.end());
    }
}

static void stdSort(benchmark::State &state) {
    const int n = state.range(0);
    auto gen = std::bind(std::uniform_int_distribution<int>(), std::mt19937());
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = gen();
    std::sort(a.begin(), a.end());
    std::vector<int> b;
    for (auto s : state) {
        b = a;
        std::sort(b.begin(), b.end());
    }
}
BENCHMARK(hybridSort)->RangeMultiplier(2)->Range(1, 1 << 23)->Arg(10000000);
BENCHMARK(stdSort)->RangeMultiplier(2)->Range(1, 1 << 23)->Arg(10000000);
BENCHMARK_MAIN();
