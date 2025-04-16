# ParallelMST

A parallel implementation of Minimum Spanning Tree (MST) algorithms using OpenMP, featuring both Kruskal's and Prim's algorithms.

## Quick Start Guide for NYU CIMS Systems

### Setup
1. Clone and enter the repository:
```bash
git clone https://github.com/Prithviraj8/parallelizing_mst.git
cd parallelizing_mst/src
```

2. Build both sequential and parallel versions:
```bash
# Build sequential version
cd Sequential && make sequential_mst
cd ..

# Build parallel version
cd Parallel && make parallel
cd ..

# Build edge generator
g++ -std=c++14 generate_edges.cpp -o edges
```

### Running Tests
The project includes two test scripts that will automatically test both sequential and parallel implementations:

1. For sequential tests:
```bash
./run_tests_seq.sh
```

2. For parallel tests:
```bash
./run_tests.sh
```

Both scripts will:
- Generate test graphs automatically
- Run all sorting methods (Bubble, Quick, and Merge Sort)
- Save results in the `results` directory

### Test Configurations
The tests cover three graph sizes:
- Small: 100 vertices, 4000 edges
- Medium: 1000 vertices, 20000 edges
- Large: 1500 vertices, 50000 edges

### Manual Testing (if needed)

1. Generate a custom graph:
```bash
./edges <vertices> <edges> <output_file>
```

2. Run sequential version:
```bash
./sequential_mst <vertices> <edges> <sorting_algo> <edges_file>
```

3. Run parallel version:
```bash
./parallel_mst <num_threads> <vertices> <edges> <sorting_algo> <edges_file>
```

Where:
- sorting_algo: 1 (Bubble Sort), 2 (Quick Sort), 3 (Merge Sort)
- num_threads: Number of OpenMP threads (1, 2, 4, or 8 recommended)

### Important Notes
- After building, both executables (`sequential_mst` and `parallel_mst`) will be in the root `src` directory
- Make sure to set execute permissions if needed:
  ```bash
  chmod +x sequential_mst parallel_mst
  ```

## Requirements
- C++14 compiler (available on CIMS machines)
- OpenMP (pre-installed on CIMS machines)

## Results
Test results will be saved in the `results` directory, showing execution times and MST weights for each configuration.

For detailed performance analysis and implementation details, please refer to the project report.
