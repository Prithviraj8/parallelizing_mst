// Sequential Sorting Algorithms
#include "sequential_sort.h"
#include <algorithm>
#include <stdexcept>


// ========================================
// Bubble Sort
// ========================================
void SequentialBubbleSort(std::vector<std::vector<int>>& edgeList) {
    const int n = edgeList.size();
    bool swapped;

    // Optimization: Use swapped flag to detect if array is already sorted
    for (int phase = 0; phase < n - 1; phase++) {
        swapped = false;
        
        // Compare adjacent elements and swap if needed
        for (int i = 0; i < n - phase - 1; i++) {
            // Compare first by weight, then by source vertex, then by destination vertex
            // for consistency with other sorting methods
            bool shouldSwap = false;
            if (edgeList[i][0] > edgeList[i + 1][0]) {
                shouldSwap = true;
            } else if (edgeList[i][0] == edgeList[i + 1][0]) {
                if (edgeList[i][1] > edgeList[i + 1][1]) {
                    shouldSwap = true;
                } else if (edgeList[i][1] == edgeList[i + 1][1] && 
                         edgeList[i][2] > edgeList[i + 1][2]) {
                    shouldSwap = true;
                }
            }
            
            if (shouldSwap) {
                std::swap(edgeList[i], edgeList[i + 1]);
                swapped = true;
            }
        }

        // If no swapping occurred, array is already sorted
        if (!swapped) {
            break;
        }
    }
}


// ========================================
// Quick Sort
// ========================================
void SequentialQuickSort(std::vector<std::vector<int>>& edgeList, int low, int high) {
    if (low < high) {
        // Choose middle element as pivot
        std::vector<int> pivot = edgeList[high];  // Use last element as pivot
        int i = low - 1;
        
        // Partition around pivot using stable comparison
        for (int j = low; j < high; j++) {
            // Compare first by weight, then by source vertex, then by destination vertex
            bool shouldSwap = false;
            if (edgeList[j][0] < pivot[0]) {
                shouldSwap = true;
            } else if (edgeList[j][0] == pivot[0]) {
                if (edgeList[j][1] < pivot[1]) {
                    shouldSwap = true;
                } else if (edgeList[j][1] == pivot[1] && edgeList[j][2] < pivot[2]) {
                    shouldSwap = true;
                }
            }
            
            if (shouldSwap) {
                i++;
                std::swap(edgeList[i], edgeList[j]);
            }
        }
        
        // Place pivot in its final position
        std::swap(edgeList[i + 1], edgeList[high]);
        
        // Recursively sort sub-arrays
        SequentialQuickSort(edgeList, low, i);
        SequentialQuickSort(edgeList, i + 2, high);
    }
}


// ========================================
// Merge Sort
// ========================================
void merge(std::vector<std::vector<int>>& edgeList, int left, int mid, int right) {
    const int leftSize = mid - left + 1;
    const int rightSize = right - mid;
    
    // Create temporary arrays for merging
    std::vector<std::vector<int>> leftArray(leftSize);
    std::vector<std::vector<int>> rightArray(rightSize);
    
    // Copy data to temporary arrays
    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = edgeList[left + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = edgeList[mid + 1 + i];
    }
    
    // Merge the arrays back using stable comparison
    int i = 0, j = 0, k = left;
    while (i < leftSize && j < rightSize) {
        bool useLeft = true;
        if (leftArray[i][0] > rightArray[j][0]) {
            useLeft = false;
        } else if (leftArray[i][0] == rightArray[j][0]) {
            if (leftArray[i][1] > rightArray[j][1]) {
                useLeft = false;
            } else if (leftArray[i][1] == rightArray[j][1] && 
                      leftArray[i][2] > rightArray[j][2]) {
                useLeft = false;
            }
        }
        
        if (useLeft) {
            edgeList[k] = leftArray[i];
            i++;
        } else {
            edgeList[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements
    while (i < leftSize) {
        edgeList[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        edgeList[k] = rightArray[j];
        j++;
        k++;
    }
}

void SequentialMergeSort(std::vector<std::vector<int>>& edgeList, int left, int right) {
    if (left < right) {
        // Use middle point to divide array into two halves
        const int mid = left + (right - left) / 2;
        
        // Sort first and second halves recursively
        SequentialMergeSort(edgeList, left, mid);
        SequentialMergeSort(edgeList, mid + 1, right);
        
        // Merge the sorted halves
        merge(edgeList, left, mid, right);
    }
}
