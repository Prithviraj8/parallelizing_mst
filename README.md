# ParallelMST

A parallel implementation of Minimum Spanning Tree (MST) algorithms using OpenMP. This project implements three classic MST algorithms in both sequential and parallel versions.

[![GitHub](https://img.shields.io/badge/GitHub-Repository-blue)](https://github.com/Prithviraj8/parallelizing_mst)

## Implemented Algorithms

- Kruskal's Algorithm
- Prim's Algorithm
- Boruvka's Algorithm

## Features

- Parallel implementations using OpenMP
- Multiple sorting algorithm options
- Performance comparison between sequential and parallel versions
- Graph generation utility

## Sequential Implementations Validation

All three sequential MST algorithms have been tested on various graph sizes and densities to validate correctness and performance:

### 1. Large Graph (100 vertices, 1000 edges)
- MST Weight: 622
- Performance:
  - Prim's: 0.000300 seconds
  - Kruskal's: 0.001256 seconds
  - Boruvka's: 0.000433 seconds

### 2. Medium Graph (50 vertices, 100 edges)
- MST Weight: 222
- Performance:
  - Prim's: 0.000071 seconds
  - Kruskal's: 0.000126 seconds
  - Boruvka's: 0.000109 seconds

### 3. Dense Graph (10 vertices, 45 edges)
- MST Weight: 19
- Performance:
  - Prim's: 0.000020 seconds
  - Kruskal's: 0.000047 seconds
  - Boruvka's: 0.000031 seconds

All implementations yield the same MST weight for each test case, confirming their correctness. Performance patterns show Prim's algorithm is generally fastest for these test cases, followed by Boruvka's and then Kruskal's.

## Prerequisites

### 1. **System Requirements**:
- Multi-core processor
- Sufficient memory for large graphs
- Linux/macOS environment

### 2. **Dependencies**:
- C++ Compiler (g++ recommended)
- OpenMP for parallelism
- C++11 or later

## Installation

1. Clone the repository:
```bash
git clone https://github.com/Prithviraj8/parallelizing_mst.git
cd parallelizing_mst
```

2. Build the project:
```bash
cd src/Sequential && make sequential
cd ../Parallel && make parallel
cd ../
```

3. Build the edge generator:
```bash
g++ -std=c++11 -o edges GenerateEdges.cpp
```

## Usage

1. Generate a graph:
```bash
./edges <vertices> <edges> <edges_out_file>
```

2. Run parallel implementation:
```bash
./parallel <num_threads> <vertices> <edges> <sorting_algo> <edges_file>
```

3. Run sequential implementation:
```bash
./sequential <vertices> <edges> <sorting_algo> <edges_file>
```

## Sorting Algorithms

### Parallel Implementation (6 options):
1. In-built parallel_sort
2. Parallel Bubble Sort
3. Parallel Quick Sort
4. Parallel Merge Sort
5. Naive Parallel Bitonic Sort
6. Optimized Bitonic Sort

### Sequential Implementation (5 options):
1. In-built STL sort
2. Bubble Sort
3. Quick Sort
4. Merge Sort
5. Naive Bitonic Sort

## Example

```bash
# Generate a graph with 4000 vertices and 1,000,000 edges
./edges 4000 1000000 edges.txt

# Run parallel implementation with 4 threads using Optimized Bitonic Sort
./parallel 4 4000 1000000 6 edges.txt
```

## Performance

The project includes timing measurements for both sequential and parallel implementations, allowing for performance comparison across different algorithms and thread counts.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
