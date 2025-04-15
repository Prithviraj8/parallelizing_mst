// Sequential Sorting Algorithms
#include "sequential_sort.h"


// ========================================
// Bubble Sort
// ========================================
void SequentialBubbleSort(std::vector<std::vector<int>>& edgeList) {
    int n = edgeList.size();

    for (int phase = 0; phase < n; phase++) {
        if (phase % 2 == 0) {
            // Even phase: Compare and swap pairs (1, 2), (3, 4), ...
            for (int i = 1; i < n; i += 2) {
                if (edgeList[i - 1] > edgeList[i]) {
                    std::swap(edgeList[i - 1], edgeList[i]);
                }
            }
        } else {
            // Odd phase: Compare and swap pairs (2, 3), (4, 5), ...
            for (int i = 1; i < n - 1; i += 2) {
                if (edgeList[i] > edgeList[i + 1]) {
                    std::swap(edgeList[i], edgeList[i + 1]);
                }
            }
        }
    }
}


// ========================================
// Quick Sort
// ========================================
void SequentialQuickSort(std::vector<std::vector<int>>& edgeList, int low, int high) {
    if (low < high) {
        int pivot = edgeList[low + (high - low) / 2][0]; // Choose pivot
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (edgeList[j][0] < pivot) {
                i++;
                std::swap(edgeList[i], edgeList[j]);
            }
        }
        std::swap(edgeList[i + 1], edgeList[high]);
        int pi = i + 1;

        // Recursively sort left and right halves
        SequentialQuickSort(edgeList, low, pi - 1);
        SequentialQuickSort(edgeList, pi + 1, high);
    }
}


// ========================================
// Merge Sort
// ========================================
void merge(std::vector<std::vector<int>>& edgeList, int left, int mid, int right) {
    std::vector<std::vector<int>> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (edgeList[i] <= edgeList[j]) {
            temp[k++] = edgeList[i++];
        } else {
            temp[k++] = edgeList[j++];
        }
    }

    while (i <= mid) temp[k++] = edgeList[i++];
    while (j <= right) temp[k++] = edgeList[j++];

    for (int i = left, k = 0; i <= right; i++, k++) {
        edgeList[i] = temp[k];
    }
}

void SequentialMergeSort(std::vector<std::vector<int>>& edgeList, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort left and right halves
        SequentialMergeSort(edgeList, left, mid);
        SequentialMergeSort(edgeList, mid + 1, right);

        // Merge the sorted halves
        merge(edgeList, left, mid, right);
    }
}
