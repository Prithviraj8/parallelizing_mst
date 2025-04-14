// parallel_sort.h
#ifndef PARALLEL_SORT_H
#define PARALLEL_SORT_H

#include <vector>
#include <algorithm>
#include <omp.h>
#include <climits> // For INT_MAX

// Function declarations for parallel sorting algorithms
void parallelBubbleSort(std::vector<std::vector<int> >& edgeList, int NUMTHREADS);

void parallelQuickSort(std::vector<std::vector<int> >& edgeList, int NUMTHREADS);
void quickSort_parallel_internal(std::vector<std::vector<int> >& edgeList, int left, int right, int cutoff);

void parallelMergeSort(std::vector<std::vector<int> >& edgeList, int NUMTHREADS);
void parallelMerge(std::vector<std::vector<int> >& edgeList, int left, int mid, int right);
void parallelMergeSort_internal(std::vector<std::vector<int> >& edgeList, int left, int right, int cutoff);

#endif // PARALLEL_SORT_H
