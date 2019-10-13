/**
 * Radix Sort
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
#ifndef _RADIX_SORT_HPP_
#define _RADIX_SORT_HPP_
#include <cstring>
#include <algorithm>

namespace HybridSort {
    template <typename T>
    void radixSort(T *a, int n) {
        std::sort(a, a + n);
    }

    template <>
    void radixSort<unsigned int>(unsigned int *a, int n) {
        using T = unsigned int;
        T *b = new T[n];

        static unsigned int buf[256];

        memset(buf, 0, sizeof(unsigned int) * 256);
        for (int i = 0; i < n; i++) buf[a[i] & 255]++;
        for (int i = 1; i < 256; i++) buf[i] += buf[i - 1];
        for (int i = n - 1; i >= 0; i--) b[--buf[a[i] & 255]] = a[i];

        memset(buf, 0, sizeof(unsigned int) * 256);
        for (int i = 0; i < n; i++) buf[(b[i] >> 8) & 255]++;
        for (int i = 1; i < 256; i++) buf[i] += buf[i - 1];
        for (int i = n - 1; i >= 0; i--) a[--buf[(b[i] >> 8) & 255]] = b[i];

        memset(buf, 0, sizeof(unsigned int) * 256);
        for (int i = 0; i < n; i++) buf[(a[i] >> 16) & 255]++;
        for (int i = 1; i < 256; i++) buf[i] += buf[i - 1];
        for (int i = n - 1; i >= 0; i--) b[--buf[(a[i] >> 16) & 255]] = a[i];

        memset(buf, 0, sizeof(unsigned int) * 256);
        for (int i = 0; i < n; i++) buf[(b[i] >> 24) & 255]++;
        for (int i = 1; i < 256; i++) buf[i] += buf[i - 1];
        for (int i = n - 1; i >= 0; i--) a[--buf[(b[i] >> 24) & 255]] = b[i];
        delete[] b;
    }

    template <>
    void radixSort<unsigned short>(unsigned short *a, int n) {
        using T = unsigned short;
        T *b = new T[n];

        static unsigned int buf[256];

        memset(buf, 0, sizeof(unsigned int) * 256);
        for (int i = 0; i < n; i++) buf[a[i] & 255]++;
        for (int i = 1; i < 256; i++) buf[i] += buf[i - 1];
        for (int i = n - 1; i >= 0; i--) b[--buf[a[i] & 255]] = a[i];

        memset(buf, 0, sizeof(unsigned int) * 256);
        for (int i = 0; i < n; i++) buf[(b[i] >> 8) & 255]++;
        for (int i = 1; i < 256; i++) buf[i] += buf[i - 1];
        for (int i = n - 1; i >= 0; i--) a[--buf[(b[i] >> 8) & 255]] = b[i];
        delete[] b;
    }

    template <>
    void radixSort<unsigned char>(unsigned char *a, int n) {
        using T = unsigned char;
        T *b = new T[n];

        static unsigned int buf[256];

        memset(buf, 0, sizeof(unsigned int) * 256);
        for (int i = 0; i < n; i++) buf[a[i] & 255]++;
        for (int i = 1; i < 256; i++) buf[i] += buf[i - 1];
        for (int i = n - 1; i >= 0; i--) b[--buf[a[i] & 255]] = a[i];
        memcpy(a, b, sizeof(T) * n);
        delete[] b;
    }

    template <>
    void radixSort<char>(char *a, int n) {
        radixSort((unsigned char *)a, n);
    }

    template <>
    void radixSort<short>(short *a, int n) {
        radixSort((unsigned short *)a, n);
    }

    template <>
    void radixSort<int>(int *a, int n) {
        radixSort((unsigned int *)a, n);
    }

}  // namespace HybridSort
#endif