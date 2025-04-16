#!/bin/bash

# First compile the parallel implementations
echo "=== Compiling parallel implementations ==="
cd Parallel
make clean
make parallel
if [ ! -f ../parallel_mst ]; then
    echo "Error: Failed to compile parallel implementation"
    exit 1
fi
cd ..

# Arrays for vertices and edges
# Edges = V*(V-1)/2
vertices=(100 1000 1500)
edges=(4000 20000 50000)

# Sorting methods to test
# 1: Bubble Sort
# 2: Quick Sort
# 3: Merge Sort
sorting_methods=(1 2 3)

# Compile the edge generator if not already compiled
g++ -std=c++14 generate_edges.cpp -o edges
if [ ! -f edges ]; then
    echo "Error: Failed to compile edge generator"
    exit 1
fi

# Create results directory
mkdir -p results

# Run tests for each configuration
for i in {0..2}; do
    v=${vertices[$i]}
    e=${edges[$i]}
    
    echo "=== Testing configuration: $v vertices, $e edges ==="
    
    # Generate graph
    echo "Generating graph..."
    ./edges $v $e "graph_${v}_${e}.txt"
    
    # Test each sorting method
    for sort in "${sorting_methods[@]}"; do
        echo -e "\n=== Using sorting method $sort ==="
        
        # Run tests with different thread counts
        for threads in 1 2 4 8; do
            echo -e "\nTesting with $threads thread(s):"
            ./parallel_mst $threads $v $e $sort "graph_${v}_${e}.txt" | tee -a "results/results_${v}_${e}_sort${sort}.txt"
        done
    done
    
    echo -e "\nCompleted testing for $v vertices, $e edges\n"
    echo "----------------------------------------"
done

# Cleanup temporary graph files
rm -f graph_*.txt

echo "All tests completed. Results are saved in the results directory." 