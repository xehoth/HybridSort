/**
 * Hrbrid Sort Test Random
 *
 * Copyright (c) 2019, xehoth
 * All rights reserved.
 *
 * Licensed under the MIT License;
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @author xehoth
 */
#include <iostream>
#include <algorithm>
#include <random>
#include <functional>
#include <cstdlib>
#include "../HybridSort.hpp"

void testInt() {
    static auto gen = std::bind(std::uniform_int_distribution<>(), std::mt19937());
    const int n = gen() % 20000000 + 1;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = gen();
    HybridSort::sort(a.begin(), a.end());
    if (!std::is_sorted(a.begin(), a.end())) {
        std::cout << "failed on int test" << std::endl;
        exit(0);
    }
}

void testUint() {
    static auto gen = std::bind(std::uniform_int_distribution<unsigned int>(), std::mt19937());
    const int n = gen() % 20000000 + 1;
    std::vector<unsigned int> a(n);
    for (int i = 0; i < n; i++) a[i] = gen();
    HybridSort::sort(a.begin(), a.end());
    if (!std::is_sorted(a.begin(), a.end())) {
        std::cout << "failed on unsigned int test" << std::endl;
        exit(0);
    }
}

void testChar() {
    static auto gen = std::bind(std::uniform_int_distribution<char>(), std::mt19937());
    const int n = gen() % 20000000 + 1;
    std::vector<char> a(n);
    for (int i = 0; i < n; i++) a[i] = gen();
    HybridSort::sort(a.begin(), a.end());
    if (!std::is_sorted(a.begin(), a.end())) {
        std::cout << "failed on char test" << std::endl;
        exit(0);
    }
}

void testUchar() {
    static auto gen = std::bind(std::uniform_int_distribution<unsigned char>(), std::mt19937());
    const int n = gen() % 20000000 + 1;
    std::vector<unsigned char> a(n);
    for (int i = 0; i < n; i++) a[i] = gen();
    HybridSort::sort(a.begin(), a.end());
    if (!std::is_sorted(a.begin(), a.end())) {
        std::cout << "failed on unsigned char test" << std::endl;
        exit(0);
    }
}

void testLongLong() {
    static auto gen = std::bind(std::uniform_int_distribution<long long>(), std::mt19937_64());
    const int n = gen() % 20000000 + 1;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) a[i] = gen();
    HybridSort::sort(a.begin(), a.end());
    if (!std::is_sorted(a.begin(), a.end())) {
        std::cout << "failed on long long test" << std::endl;
        exit(0);
    }
}

void testUlongLong() {
    static auto gen =
        std::bind(std::uniform_int_distribution<unsigned long long>(), std::mt19937_64());
    const int n = gen() % 20000000 + 1;
    std::vector<unsigned long long> a(n);
    for (int i = 0; i < n; i++) a[i] = gen();
    HybridSort::sort(a.begin(), a.end());
    if (!std::is_sorted(a.begin(), a.end())) {
        std::cout << "failed on unsigned long long test" << std::endl;
        exit(0);
    }
}

void testDouble() {
    static auto genN = std::bind(std::uniform_int_distribution<>(), std::mt19937());
    static auto gen = std::bind(std::uniform_real_distribution<>(), std::mt19937());
    const int n = genN() % 20000000 + 1;
    std::vector<double> a(n);
    for (int i = 0; i < n; i++) a[i] = gen();
    HybridSort::sort(a.begin(), a.end());
    if (!std::is_sorted(a.begin(), a.end())) {
        std::cout << "failed on double test" << std::endl;
        exit(0);
    }
}

void testFloat() {
    static auto genN = std::bind(std::uniform_int_distribution<>(), std::mt19937());
    static auto gen = std::bind(std::uniform_real_distribution<float>(), std::mt19937());
    const int n = genN() % 20000000 + 1;
    std::vector<float> a(n);
    for (int i = 0; i < n; i++) a[i] = gen();
    HybridSort::sort(a.begin(), a.end());
    if (!std::is_sorted(a.begin(), a.end())) {
        std::cout << "failed on float test" << std::endl;
        exit(0);
    }
}

int main() {
    const int TEST_CNT = 10;
    std::vector<std::function<void()> > tests{testInt,      testUint,      testChar,   testUchar,
                                              testLongLong, testUlongLong, testDouble, testFloat};
    for (auto f : tests)
        for (int i = 0; i < TEST_CNT; i++) f();
    std::cout << "all tests pass" << std::endl;
}