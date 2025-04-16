# ParallelMST

A parallel implementation of Minimum Spanning Tree (MST) algorithms using OpenMP, featuring both Kruskal's and Prim's algorithms.

## Quick Start Guide for NYU CIMS Systems

### Setup
1. Clone and enter the repository:
```bash
git clone https://github.com/Prithviraj8/parallelizing_mst.git
cd parallelizing_mst
```

2. Build all components:
```bash
cd src

# Build sequential version
cd Sequential && make clean && make
cd ..

# Build parallel version
cd Parallel && make clean && make
cd ..

# Build edge generator
g++ -std=c++14 generate_edges.cpp -o edges
```

### Running Tests
The project includes two test scripts that will automatically test both implementations:

1. For sequential tests:
```bash
cd src
bash scripts/run_tests_seq.sh
```

2. For parallel tests:
```bash
cd src
bash scripts/run_tests.sh
```

Both scripts will:
- Compile the necessary components
- Generate test graphs automatically
- Run all sorting methods (Bubble, Quick, and Merge Sort)
- For parallel tests, run with different thread counts (1, 2, 4, 8)
- Save results in the `results` directory

### Test Configurations
The tests cover three graph sizes:
- Small: 100 vertices, 4000 edges
- Medium: 1000 vertices, 20000 edges
- Large: 1500 vertices, 50000 edges

### Manual Testing (if needed)

1. Generate a custom graph:
```bash
cd src
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
- edges_file: Input file containing the graph edges

### Directory Structure
```
parallelizing_mst/
├── src/
│   ├── Sequential/     # Sequential implementation
│   ├── Parallel/       # Parallel implementation with OpenMP
│   ├── scripts/        # Test scripts
│   ├── results/        # Test results
│   ├── edges          # Edge generator executable
│   ├── sequential_mst # Sequential MST executable
│   └── parallel_mst   # Parallel MST executable
```

### Important Notes
- All executables will be generated in the `src` directory
- Make sure to run all commands from the `src` directory
- The test scripts will handle all compilation and file management
- Results will be displayed in the terminal and relevant metrics saved in the `results` directory

## Requirements
- C++14 compiler (available on CIMS machines)
- OpenMP (pre-installed on CIMS machines)
- GNU Make (pre-installed on CIMS machines)

## Results
Test results will be displayed in the terminal, showing:
- MST weights (to verify correctness)
- Execution times for each configuration
- Speedup metrics for parallel implementation

For detailed performance analysis and implementation details, please refer to the project report.
