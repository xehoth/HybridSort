/**
 * C++ implementation of dual pivot quick sort
 *
 * ported from java
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
#ifndef _DUAL_PIVOT_QUICK_SORT_HPP_
#define _DUAL_PIVOT_QUICK_SORT_HPP_

#include <algorithm>
#include <cstring>

namespace HybridSort {

    /**
     * The maximum number of runs in merge dualPivotQuickSort.
     */
    const int MAX_RUN_COUNT = 67;

    /**
     * The maximum length of run in merge dualPivotQuickSort.
     */
    const int MAX_RUN_LENGTH = 33;

    /**
     * If the length of an array to be sorted is less than this
     * constant, Quicksort is used in preference to merge dualPivotQuickSort.
     */
    const int QUICKSORT_THRESHOLD = 286;

    /**
     * If the length of an array to be sorted is less than this
     * constant, insertion dualPivotQuickSort is used in preference to Quicksort.
     */
    const int INSERTION_SORT_THRESHOLD = 47;

    /**
     * Sorts the specified range of the array by Dual-Pivot Quicksort.
     *
     * @param a the array to be sorted
     * @param left the index of the first element, inclusive, to be sorted
     * @param right the index of the last element, inclusive, to be sorted
     * @param leftmost indicates if this part is the leftmost in the range
     */
    template <typename T>
    void dualPivotQuickSort(T *a, int left, int right, bool leftmost) {
        int length = right - left + 1;

        // Use insertion dualPivotQuickSort on tiny arrays
        if (length < INSERTION_SORT_THRESHOLD) {
            if (leftmost) {
                /*
                 * Traditional (without sentinel) insertion dualPivotQuickSort,
                 * optimized for server VM, is used in case of
                 * the leftmost part.
                 */
                for (int i = left, j = i; i < right; j = ++i) {
                    T ai = a[i + 1];
                    while (ai < a[j]) {
                        a[j + 1] = a[j];
                        if (j-- == left) break;
                    }
                    a[j + 1] = ai;
                }
            } else {
                /*
                 * Skip the longest ascending sequence.
                 */
                do {
                    if (left >= right) return;
                    ++left;
                } while (a[left] >= a[left - 1]);

                /*
                 * Every element from adjoining part plays the role
                 * of sentinel, therefore this allows us to avoid the
                 * left range check on each iteration. Moreover, we use
                 * the more optimized algorithm, so called pair insertion
                 * dualPivotQuickSort, which is faster (in the context of Quicksort)
                 * than traditional implementation of insertion dualPivotQuickSort.
                 */
                for (int k = left; ++left <= right; k = ++left) {
                    T a1 = a[k], a2 = a[left];

                    if (a1 < a2) {
                        a2 = a1;
                        a1 = a[left];
                    }
                    while (a1 < a[--k]) a[k + 2] = a[k];
                    a[++k + 1] = a1;

                    while (a2 < a[--k]) a[k + 1] = a[k];
                    a[k + 1] = a2;
                }
                T last = a[right];

                while (last < a[--right]) a[right + 1] = a[right];
                a[right + 1] = last;
            }
            return;
        }

        // Inexpensive approximation of length / 7
        int seventh = (length >> 3) + (length >> 6) + 1;

        /*
         * Sort five evenly spaced elements around (and including) the
         * center element in the range. These elements will be used for
         * pivot selection as described below. The choice for spacing
         * these elements was empirically determined to work well on
         * a wide variety of inputs.
         */
        int e3 = static_cast<unsigned int>(left + right) >> 1;  // The midpoint
        int e2 = e3 - seventh;
        int e1 = e2 - seventh;
        int e4 = e3 + seventh;
        int e5 = e4 + seventh;

        // Sort these elements using insertion dualPivotQuickSort
        if (a[e2] < a[e1]) std::swap(a[e2], a[e1]);

        if (a[e3] < a[e2]) {
            std::swap(a[e3], a[e2]);
            if (a[e2] < a[e1]) std::swap(a[e2], a[e1]);
        }
        if (a[e4] < a[e3]) {
            std::swap(a[e4], a[e3]);
            if (a[e3] < a[e2]) {
                std::swap(a[e3], a[e2]);
                if (a[e2] < a[e1]) std::swap(a[e2], a[e1]);
            }
        }
        if (a[e5] < a[e4]) {
            std::swap(a[e5], a[e4]);
            if (a[e4] < a[e3]) {
                std::swap(a[e4], a[e3]);
                if (a[e3] < a[e2]) {
                    std::swap(a[e3], a[e2]);
                    if (a[e2] < a[e1]) std::swap(a[e2], a[e1]);
                }
            }
        }

        // Pointers
        int less = left;    // The index of the first element of center part
        int great = right;  // The index before the first element of right part

        if (a[e1] != a[e2] && a[e2] != a[e3] && a[e3] != a[e4] && a[e4] != a[e5]) {
            /*
             * Use the second and fourth of the five sorted elements as pivots.
             * These values are inexpensive approximations of the first and
             * second terciles of the array. Note that pivot1 <= pivot2.
             */
            T pivot1 = a[e2];
            T pivot2 = a[e4];

            /*
             * The first and the last elements to be sorted are moved to the
             * locations formerly occupied by the pivots. When partitioning
             * is complete, the pivots are swapped back into their const
             * positions, and excluded from subsequent sorting.
             */
            a[e2] = a[left];
            a[e4] = a[right];

            /*
             * Skip elements, which are less or greater than pivot values.
             */
            while (a[++less] < pivot1)
                ;
            while (a[--great] > pivot2)
                ;

        /*
         * Partitioning:
         *
         *   left part           center part                   right part
         * +--------------------------------------------------------------+
         * |  < pivot1  |  pivot1 <= && <= pivot2  |    ?    |  > pivot2  |
         * +--------------------------------------------------------------+
         *               ^                          ^       ^
         *               |                          |       |
         *              less                        k     great
         *
         * Invariants:
         *
         *              all in (left, less)   < pivot1
         *    pivot1 <= all in [less, k)     <= pivot2
         *              all in (great, right) > pivot2
         *
         * Pointer k is the first index of ?-part.
         */
        outer1:
            for (int k = less - 1; ++k <= great;) {
                T ak = a[k];
                if (ak < pivot1) {  // Move a[k] to left part
                    std::swap(a[k], a[less++]);
                } else if (ak > pivot2) {  // Move a[k] to right part
                    while (a[great] > pivot2)
                        if (great-- == k) goto outer1;
                    if (a[great] < pivot1) {  // a[great] <= pivot2
                        a[k] = a[less];
                        a[less++] = a[great];
                    } else {  // pivot1 <= a[great] <= pivot2
                        a[k] = a[great];
                    }
                    a[great--] = ak;
                }
            }

            // Swap pivots into their const positions
            a[left] = a[less - 1];
            a[less - 1] = pivot1;
            a[right] = a[great + 1];
            a[great + 1] = pivot2;

            // Sort left and right parts recursively, excluding known pivots
            dualPivotQuickSort(a, left, less - 2, leftmost);
            dualPivotQuickSort(a, great + 2, right, false);

            /*
             * If center part is too large (comprises > 4/7 of the array),
             * swap internal pivot values to ends.
             */
            if (less < e1 && e5 < great) {
                /*
                 * Skip elements, which are equal to pivot values.
                 */
                while (a[less] == pivot1) ++less;
                while (a[great] == pivot2) --great;

            /*
             * Partitioning:
             *
             *   left part         center part                  right part
             * +----------------------------------------------------------+
             * | == pivot1 |  pivot1 < && < pivot2  |    ?    | == pivot2 |
             * +----------------------------------------------------------+
             *              ^                        ^       ^
             *              |                        |       |
             *             less                      k     great
             *
             * Invariants:
             *
             *              all in (*,  less) == pivot1
             *     pivot1 < all in [less,  k)  < pivot2
             *              all in (great, *) == pivot2
             *
             * Pointer k is the first index of ?-part.
             */
            outer2:
                for (int k = less - 1; ++k <= great;) {
                    T ak = a[k];
                    if (ak == pivot1) {  // Move a[k] to left part
                        std::swap(a[k], a[less++]);
                    } else if (ak == pivot2) {  // Move a[k] to right part
                        while (a[great] == pivot2)
                            if (great-- == k) goto outer2;
                        if (a[great] == pivot1) {  // a[great] < pivot2
                            a[k] = a[less];
                            /*
                             * Even though a[great] equals to pivot1, the
                             * assignment a[less] = pivot1 may be incorrect,
                             * if a[great] and pivot1 are floating-point zeros
                             * of different signs. Therefore in float and
                             * double sorting methods we have to use more
                             * accurate assignment a[less] = a[great].
                             */
                            a[less++] = pivot1;
                        } else {  // pivot1 < a[great] < pivot2
                            a[k] = a[great];
                        }
                        a[great--] = ak;
                    }
                }
            }

            // Sort center part recursively
            dualPivotQuickSort(a, less, great, false);

        } else {  // Partitioning with one pivot
            /*
             * Use the third of the five sorted elements as pivot.
             * This value is inexpensive approximation of the median.
             */
            T pivot = a[e3];

            /*
             * Partitioning degenerates to the traditional 3-way
             * (or "Dutch National Flag") schema:
             *
             *   left part    center part              right part
             * +-------------------------------------------------+
             * |  < pivot  |   == pivot   |     ?    |  > pivot  |
             * +-------------------------------------------------+
             *              ^              ^        ^
             *              |              |        |
             *             less            k      great
             *
             * Invariants:
             *
             *   all in (left, less)   < pivot
             *   all in [less, k)     == pivot
             *   all in (great, right) > pivot
             *
             * Pointer k is the first index of ?-part.
             */
            for (int k = less; k <= great; ++k) {
                if (a[k] == pivot) continue;
                T ak = a[k];
                if (ak < pivot) {  // Move a[k] to left part
                    std::swap(a[k], a[less++]);
                } else {  // a[k] > pivot - Move a[k] to right part
                    while (a[great] > pivot) --great;
                    if (a[great] < pivot) {  // a[great] <= pivot
                        a[k] = a[less];
                        a[less++] = a[great];
                    } else {  // a[great] == pivot
                        /*
                         * Even though a[great] equals to pivot, the
                         * assignment a[k] = pivot may be incorrect,
                         * if a[great] and pivot are floating-point
                         * zeros of different signs. Therefore in float
                         * and double sorting methods we have to use
                         * more accurate assignment a[k] = a[great].
                         */
                        a[k] = pivot;
                    }
                    a[great--] = ak;
                }
            }

            /*
             * Sort left and right parts recursively.
             * All elements from center part are equal
             * and, therefore, already sorted.
             */
            dualPivotQuickSort(a, left, less - 1, leftmost);
            dualPivotQuickSort(a, great + 1, right, false);
        }
    }

    /**
     * Sorts the specified range of the array using the given
     * workspace array slice if possible for merging
     *
     * @param a the array to be sorted
     * @param left the index of the first element, inclusive, to be sorted
     * @param right the index of the last element, inclusive, to be sorted
     * @param work a workspace array (slice)
     * @param workBase origin of usable space in work array
     * @param workLen usable size of work array
     */
    template <typename T>
    inline void dualPivotQuickSort(T *a, int left, int right, T *work, int workBase, int workLen,
                                   int workLength) {
        // Use Quicksort on small arrays
        if (right - left < QUICKSORT_THRESHOLD) {
            dualPivotQuickSort(a, left, right, true);
            return;
        }

        /*
         * Index run[i] is the start of i-th run
         * (ascending or descending sequence).
         */
        static int run[MAX_RUN_COUNT + 1];
        memset(run, 0, sizeof(run));
        int count = 0;
        run[0] = left;

        // Check if the array is nearly sorted
        for (int k = left; k < right; run[count] = k) {
            if (a[k] < a[k + 1]) {  // ascending
                while (++k <= right && a[k - 1] <= a[k])
                    ;
            } else if (a[k] > a[k + 1]) {  // descending
                while (++k <= right && a[k - 1] >= a[k])
                    ;
                for (int lo = run[count] - 1, hi = k; ++lo < --hi;) std::swap(a[lo], a[hi]);
            } else {  // equal
                for (int m = MAX_RUN_LENGTH; ++k <= right && a[k - 1] == a[k];) {
                    if (--m == 0) {
                        dualPivotQuickSort(a, left, right, true);
                        return;
                    }
                }
            }

            /*
             * The array is not highly structured,
             * use Quicksort instead of merge dualPivotQuickSort.
             */
            if (++count == MAX_RUN_COUNT) {
                dualPivotQuickSort(a, left, right, true);
                return;
            }
        }

        // Check special cases
        // Implementation note: variable "right" is increased by 1.
        if (run[count] == right++) {  // The last run contains one element
            run[++count] = right;
        } else if (count == 1) {  // The array is already sorted
            return;
        }

        // Determine alternation base for merge
        char odd = 0;
        for (int n = 1; (n <<= 1) < count; odd ^= 1)
            ;

        // Use or create temporary array b for merging
        T *b;                     // temp array; alternates with a
        int ao, bo;               // array offsets from 'left'
        int blen = right - left;  // space needed for b
        if (work == nullptr || workLen < blen || workBase + blen > workLength) {
            work = new T[blen]();
            workBase = 0;
        }
        if (odd == 0) {
            memcpy(work + workBase, a + left, sizeof(T) * blen);
            b = a;
            bo = 0;
            a = work;
            ao = workBase - left;
        } else {
            b = work;
            ao = 0;
            bo = workBase - left;
        }

        // Merging
        for (int last; count > 1; count = last) {
            for (int k = (last = 0) + 2; k <= count; k += 2) {
                int hi = run[k], mi = run[k - 1];
                for (int i = run[k - 2], p = i, q = mi; i < hi; ++i) {
                    if (q >= hi || (p < mi && a[p + ao] <= a[q + ao])) {
                        b[i + bo] = a[p++ + ao];
                    } else {
                        b[i + bo] = a[q++ + ao];
                    }
                }
                run[++last] = hi;
            }
            if ((count & 1) != 0) {
                for (int i = right, lo = run[count - 1]; --i >= lo; b[i + bo] = a[i + ao])
                    ;
                run[++last] = right;
            }
            std::swap(a, b);
            std::swap(ao, bo);
        }
        delete[] work;
    }

    template <typename T>
    inline void dualPivotQuickSort(T begin, T end) {
        dualPivotQuickSort(&(*begin), 0, end - begin - 1, (decltype(&(*begin))) nullptr, 0, 0, 0);
    }
}  // namespace HybridSort
#endif
