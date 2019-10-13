/**
 * Hrbrid Sort
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
#ifndef _HYBRID_SORT_HPP_
#define _HYBRID_SORT_HPP_
#include "include/DualPivotQuickSort.hpp"
#include "include/RadixSort.hpp"
#include <algorithm>
#include <functional>
#include <vector>

namespace HybridSort {
    template <typename T>
    void sort(T begin, T end) {
        std::sort(begin, end);
    }

    template <>
    void sort<float *>(float *begin, float *end) {
        if (end - begin <= 10000000) {
            dualPivotQuickSort(begin, end);
            return;
        }
        std::sort(begin, end);
    }

    template <>
    void sort<std::vector<float>::iterator>(std::vector<float>::iterator begin,
                                            std::vector<float>::iterator end) {
        if (end - begin <= 10000000) {
            dualPivotQuickSort(begin, end);
            return;
        }
        std::sort(begin, end);
    }

    template <>
    void sort<double *>(double *begin, double *end) {
        if (end - begin <= 10000000) {
            dualPivotQuickSort(begin, end);
            return;
        }
        std::sort(begin, end);
    }

    template <>
    void sort<std::vector<double>::iterator>(std::vector<double>::iterator begin,
                                             std::vector<double>::iterator end) {
        if (end - begin <= 10000000) {
            dualPivotQuickSort(begin, end);
            return;
        }
        std::sort(begin, end);
    }

    template <>
    void sort<long double *>(long double *begin, long double *end) {
        if (end - begin <= 10000000) {
            dualPivotQuickSort(begin, end);
            return;
        }
        std::sort(begin, end);
    }

    template <>
    void sort<std::vector<long double>::iterator>(std::vector<long double>::iterator begin,
                                                  std::vector<long double>::iterator end) {
        if (end - begin <= 10000000) {
            dualPivotQuickSort(begin, end);
            return;
        }
        std::sort(begin, end);
    }

    template <>
    void sort<long long *>(long long *begin, long long *end) {
        if (end - begin <= 10000000) {
            dualPivotQuickSort(begin, end);
            return;
        }
        std::sort(begin, end);
    }

    template <>
    void sort<std::vector<long long>::iterator>(std::vector<long long>::iterator begin,
                                                std::vector<long long>::iterator end) {
        if (end - begin <= 10000000) {
            dualPivotQuickSort(begin, end);
            return;
        }
        std::sort(begin, end);
    }

    template <>
    void sort<unsigned long long *>(unsigned long long *begin, unsigned long long *end) {
        if (end - begin <= 10000000) {
            dualPivotQuickSort(begin, end);
            return;
        }
        std::sort(begin, end);
    }

    template <>
    void sort<std::vector<unsigned long long>::iterator>(
        std::vector<unsigned long long>::iterator begin,
        std::vector<unsigned long long>::iterator end) {
        if (end - begin <= 10000000) {
            dualPivotQuickSort(begin, end);
            return;
        }
        std::sort(begin, end);
    }

    template <>
    void sort<char *>(char *begin, char *end) {
        if (end - begin <= 1024) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(begin, end - begin);
    }

    template <>
    void sort<std::vector<char>::iterator>(std::vector<char>::iterator begin,
                                           std::vector<char>::iterator end) {
        if (end - begin <= 1024) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(&(*begin), end - begin);
    }

    template <>
    void sort<unsigned char *>(unsigned char *begin, unsigned char *end) {
        if (end - begin <= 1024) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(begin, end - begin);
    }

    template <>
    void sort<std::vector<unsigned char>::iterator>(std::vector<unsigned char>::iterator begin,
                                                    std::vector<unsigned char>::iterator end) {
        if (end - begin <= 1024) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(&(*begin), end - begin);
    }

    template <>
    void sort<short *>(short *begin, short *end) {
        if (end - begin <= 1048576) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(begin, end - begin);
    }

    template <>
    void sort<std::vector<short>::iterator>(std::vector<short>::iterator begin,
                                            std::vector<short>::iterator end) {
        if (end - begin <= 1048576) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(&(*begin), end - begin);
    }

    template <>
    void sort<unsigned short *>(unsigned short *begin, unsigned short *end) {
        if (end - begin <= 1048576) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(begin, end - begin);
    }

    template <>
    void sort<std::vector<unsigned short>::iterator>(std::vector<unsigned short>::iterator begin,
                                                     std::vector<unsigned short>::iterator end) {
        if (end - begin <= 1048576) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(&(*begin), end - begin);
    }

    template <>
    void sort<int *>(int *begin, int *end) {
        if (end - begin <= 2097152) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(begin, end - begin);
    }

    template <>
    void sort<std::vector<int>::iterator>(std::vector<int>::iterator begin,
                                          std::vector<int>::iterator end) {
        if (end - begin <= 2097152) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(&(*begin), end - begin);
    }

    template <>
    void sort<unsigned int *>(unsigned int *begin, unsigned int *end) {
        if (end - begin <= 2097152) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(begin, end - begin);
    }

    template <>
    void sort<std::vector<unsigned int>::iterator>(std::vector<unsigned int>::iterator begin,
                                                   std::vector<unsigned int>::iterator end) {
        if (end - begin <= 2097152) {
            dualPivotQuickSort(begin, end);
            return;
        }
        radixSort(&(*begin), end - begin);
    }

    template <typename T, typename Comp>
    void sort(T begin, T end, Comp cmp) {
        std::sort(begin, end, cmp);
    }
}  // namespace HybridSort
#endif
