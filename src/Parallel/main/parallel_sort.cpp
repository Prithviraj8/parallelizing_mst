// Parallel Sorting Algorithms
#include "parallel_sort.h"
#include <algorithm>
#include <stdexcept>

// ========================================
// Parallel Bubble Sort
// ========================================
void parallelBubbleSort(std::vector<std::vector<int>>& edgeList, int NUMTHREADS) {
    if (NUMTHREADS <= 0) {
        throw std::invalid_argument("Number of threads must be positive");
    }

    const int n = edgeList.size();

    #pragma omp parallel num_threads(NUMTHREADS)
    {
        for(int i = 0; i < n; i++) {
            int first = i % 2;  // Alternate between even and odd phases

            #pragma omp for
            for(int j = first; j < n - 1; j += 2) {
                // Use stable comparison logic
                bool shouldSwap = false;
                if (edgeList[j][0] > edgeList[j + 1][0]) {
                    shouldSwap = true;
                } else if (edgeList[j][0] == edgeList[j + 1][0]) {
                    if (edgeList[j][1] > edgeList[j + 1][1]) {
                        shouldSwap = true;
                    } else if (edgeList[j][1] == edgeList[j + 1][1] && 
                             edgeList[j][2] > edgeList[j + 1][2]) {
                        shouldSwap = true;
                    }
                }
                
                if (shouldSwap) {
                    std::swap(edgeList[j], edgeList[j + 1]);
                }
            }
        }
    }
}

// ========================================
// Parallel Quick Sort
// ========================================
void parallelQuickSort(std::vector<std::vector<int>>& edgeList, int NUMTHREADS) {
    if (NUMTHREADS <= 0) {
        throw std::invalid_argument("Number of threads must be positive");
    }

    const int n = edgeList.size();
    const int scalingFactor = 100;
    const int baseCutoff = n / scalingFactor;
    const int cutoff = std::max(1000, std::min(baseCutoff / NUMTHREADS, 10000));

    #pragma omp parallel num_threads(NUMTHREADS)
    {
        #pragma omp single nowait
        {
            quickSort_parallel_internal(edgeList, 0, n - 1, cutoff);
        }
    }
}

void quickSort_parallel_internal(std::vector<std::vector<int>>& edgeList, int left, int right, int cutoff) {
    if (left >= right) return;

    int i = left, j = right;
    std::vector<int> pivot = edgeList[left + (right - left) / 2];

    // Partitioning with stable comparison
    while (i <= j) {
        while (i <= right) {
            bool shouldMove = false;
            if (edgeList[i][0] < pivot[0]) {
                shouldMove = true;
            } else if (edgeList[i][0] == pivot[0]) {
                if (edgeList[i][1] < pivot[1]) {
                    shouldMove = true;
                } else if (edgeList[i][1] == pivot[1] && 
                         edgeList[i][2] < pivot[2]) {
                    shouldMove = true;
                }
            }
            if (!shouldMove) break;
            i++;
        }

        while (j >= left) {
            bool shouldMove = false;
            if (edgeList[j][0] > pivot[0]) {
                shouldMove = true;
            } else if (edgeList[j][0] == pivot[0]) {
                if (edgeList[j][1] > pivot[1]) {
                    shouldMove = true;
                } else if (edgeList[j][1] == pivot[1] && 
                         edgeList[j][2] > pivot[2]) {
                    shouldMove = true;
                }
            }
            if (!shouldMove) break;
            j--;
        }

        if (i <= j) {
            std::swap(edgeList[i], edgeList[j]);
            i++;
            j--;
        }
    }

    // Sequential recursion for small partitions
    if ((right - left) < cutoff) {
        if (left < j)
            quickSort_parallel_internal(edgeList, left, j, cutoff);
        if (i < right)
            quickSort_parallel_internal(edgeList, i, right, cutoff);
    } else {
        // Parallel tasks for larger partitions
        #pragma omp task shared(edgeList)
        quickSort_parallel_internal(edgeList, left, j, cutoff);

        #pragma omp task shared(edgeList)
        quickSort_parallel_internal(edgeList, i, right, cutoff);

        #pragma omp taskwait
    }
}

// ========================================
// Parallel Merge Sort
// ========================================
void parallelMerge(std::vector<std::vector<int>>& edgeList, int left, int mid, int right) {
    std::vector<std::vector<int>> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        bool useLeft = true;
        if (edgeList[i][0] > edgeList[j][0]) {
            useLeft = false;
        } else if (edgeList[i][0] == edgeList[j][0]) {
            if (edgeList[i][1] > edgeList[j][1]) {
                useLeft = false;
            } else if (edgeList[i][1] == edgeList[j][1] && 
                      edgeList[i][2] > edgeList[j][2]) {
                useLeft = false;
            }
        }
        
        if (useLeft) {
            temp[k++] = edgeList[i++];
        } else {
            temp[k++] = edgeList[j++];
        }
    }

    while (i <= mid) temp[k++] = edgeList[i++];
    while (j <= right) temp[k++] = edgeList[j++];

    std::copy(temp.begin(), temp.end(), edgeList.begin() + left);
}

void parallelMergeSort_internal(std::vector<std::vector<int>>& edgeList, int left, int right, int cutoff) {
    if (left < right) {
        const int mid = left + (right - left) / 2;

        if ((right - left) > cutoff) {
            #pragma omp task shared(edgeList)
            parallelMergeSort_internal(edgeList, left, mid, cutoff);

            #pragma omp task shared(edgeList)
            parallelMergeSort_internal(edgeList, mid + 1, right, cutoff);

            #pragma omp taskwait
        } else {
            parallelMergeSort_internal(edgeList, left, mid, cutoff);
            parallelMergeSort_internal(edgeList, mid + 1, right, cutoff);
        }

        parallelMerge(edgeList, left, mid, right);
    }
}

void parallelMergeSort(std::vector<std::vector<int>>& edgeList, int NUMTHREADS) {
    if (NUMTHREADS <= 0) {
        throw std::invalid_argument("Number of threads must be positive");
    }

    const int n = edgeList.size();
    const int scalingFactor = 100;
    const int baseCutoff = n / scalingFactor;
    const int cutoff = std::max(1000, std::min(baseCutoff / NUMTHREADS, 10000));

    #pragma omp parallel num_threads(NUMTHREADS)
    {
        #pragma omp single nowait
        {
            parallelMergeSort_internal(edgeList, 0, n - 1, cutoff);
        }
    }
}
