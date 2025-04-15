// Parallel Sorting Algorithms
#include "parallel_sort.h"


// ========================================
// Parallel Bubble Sort
// ========================================
void parallelBubbleSort(std::vector<std::vector<int>>& edgeList, int NUMTHREADS) {
    int n = edgeList.size();

    #pragma omp parallel num_threads(NUMTHREADS)
    {
        for(int i = 0; i < n; i ++) {
            int first = i % 2;

            #pragma omp for
            for(int j = first; j < n - 1; j += 2) {
                if(edgeList[j][0] > edgeList[j + 1][0]) {
                    std :: swap(edgeList[j], edgeList[j + 1]);
                }
            }
        }
    }
}

// ========================================
// Parallel Quick Sort
// ========================================
void parallelQuickSort(std::vector<std::vector<int>>& edgeList, int NUMTHREADS) {
    int n = edgeList.size();
    int scalingFactor = 100;

    int baseCutoff = n / scalingFactor;

    int cutoff = std::max(1000, std::min(baseCutoff / NUMTHREADS, 10000));

    #pragma omp parallel num_threads(NUMTHREADS)
    {
        #pragma omp single nowait
        {
            quickSort_parallel_internal(edgeList, 0, edgeList.size() - 1, cutoff);
        }
    }
}

void quickSort_parallel_internal(std::vector<std::vector<int>>& edgeList, int left, int right, int cutoff) {
    if (left >= right) return; // Base case for recursion

    int i = left, j = right;
    std::vector<int> pivot = edgeList[left + (right - left) / 2];

    // Partitioning
    while (i <= j) {
        while (i <= right && edgeList[i][0] < pivot[0]) i++;
        while (j >= left && edgeList[j][0] > pivot[0]) j--;
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
    std::vector<std::vector<int>> temp(right - left + 1); // Temporary buffer
    int i = left, j = mid + 1, k = 0;

    // Merge two sorted halves into the temporary array
    while (i <= mid && j <= right) {
        if (edgeList[i][0] <= edgeList[j][0]) { // Compare based on edgeList[i][0]
            temp[k++] = edgeList[i++];
        } else {
            temp[k++] = edgeList[j++];
        }
    }

    // Copy remaining elements from both halves
    while (i <= mid) temp[k++] = edgeList[i++];
    while (j <= right) temp[k++] = edgeList[j++];

    // Copy back from temporary array to original array
    std::copy(temp.begin(), temp.end(), edgeList.begin() + left);
}

void parallelMergeSort_internal(std::vector<std::vector<int>>& edgeList, int left, int right, int cutoff) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        if ((right - left) > cutoff) {
            // Create tasks for parallel execution of subproblems
            #pragma omp task shared(edgeList)
            parallelMergeSort_internal(edgeList, left, mid, cutoff);

            #pragma omp task shared(edgeList)
            parallelMergeSort_internal(edgeList, mid + 1, right, cutoff);

            #pragma omp taskwait // Wait for both tasks to complete
        } else {
            // Fallback to sequential merge sort for small partitions
            parallelMergeSort_internal(edgeList, left, mid, cutoff);
            parallelMergeSort_internal(edgeList, mid + 1, right, cutoff);
        }

        // Merge the two halves
        parallelMerge(edgeList, left, mid, right);
    }
}

void parallelMergeSort(std::vector<std::vector<int>>& edgeList, int NUMTHREADS) {
    int n = edgeList.size();              // Input size
    int scalingFactor = 100;              // Tunable scaling factor

    // Dynamically calculate base cutoff based on input size
    int baseCutoff = n / scalingFactor;

    // Adjust base cutoff based on number of threads
    int cutoff = std::max(1000, std::min(baseCutoff / NUMTHREADS, 10000));

    #pragma omp parallel num_threads(NUMTHREADS)
    {
        #pragma omp single nowait
        {
            parallelMergeSort_internal(edgeList, 0, edgeList.size() - 1, cutoff);
        }
    }
}
