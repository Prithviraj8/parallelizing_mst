#!/bin/bash

# Exit on any error
set -e

# Get the directory where the script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SRC_DIR="$( dirname "$SCRIPT_DIR" )"

# Function to run tests for a specific configuration
run_test() {
    local V=$1
    local E=$2
    
    echo "=== Testing configuration: $V vertices, $E edges ==="
    echo "Generating graph..."
    
    # Generate graph
    ./edges $V $E "graph_${V}_${E}.txt"
    
    # Test with different sorting methods
    for sort_method in 1 2 3; do
        echo -e "\n=== Using sorting method $sort_method ==="
        
        # Run sequential implementation and save output
        ./sequential_mst $V $E $sort_method "graph_${V}_${E}.txt" | tee -a "results/sequential_${V}_${E}_sort${sort_method}.txt"
        echo ""
    done
    
    echo "Completed testing for $V vertices, $E edges"
    echo -e "\n----------------------------------------"
}

# Create results directory if it doesn't exist
mkdir -p results

# Compile everything using global Makefile
echo "=== Compiling all implementations ==="
cd "$SRC_DIR"
make clean
make all
if [ ! -f sequential_mst ]; then
    echo "Error: Failed to compile sequential implementation"
    exit 1
fi

echo "=== Starting Phase 1: Basic Tests ==="

# Minimal cases
echo "Testing minimal cases..."
run_test 2 1      # Minimal connected graph
run_test 3 2      # Minimal tree
run_test 3 3      # Complete graph with 3 vertices

# Very small cases
echo "Testing very small cases..."
run_test 10 9     # Tree-like (V-1 edges)
run_test 10 20    # Sparse
run_test 10 45    # Complete graph (V*(V-1)/2 edges)

# Small cases with varying densities
echo "Testing small cases..."
run_test 50 49    # Tree-like
run_test 50 100   # Very sparse (~4% density)
run_test 50 500   # Medium density (~40% density)
run_test 50 1225  # Complete graph

# Medium cases with varying densities
echo "Testing medium cases..."
run_test 100 99    # Tree-like
run_test 100 200   # Very sparse
run_test 100 2000  # Medium density
run_test 100 4000  # Dense
run_test 100 4950  # Complete graph

# Edge cases for power of 2 sizes
echo "Testing power of 2 sizes..."
run_test 16 120    # Complete graph for power of 2
run_test 32 496    # Complete graph for power of 2
run_test 64 2016   # Complete graph for power of 2

echo "Phase 1 completed successfully."
echo -e "\n======================================\n"

echo "=== Starting Phase 2: Large Scale Tests ==="
echo "Warning: These tests may take longer to complete..."

# Large cases
echo "Testing large cases..."
run_test 500 499    # Tree-like
run_test 500 1000   # Very sparse
run_test 500 10000  # Medium density (~8%)
run_test 500 30000  # Dense (~24%)

# Very large cases
echo "Testing very large cases..."
run_test 1000 999     # Tree-like
run_test 1000 2000    # Very sparse
run_test 1000 20000   # Medium density
run_test 1000 50000   # Dense (~10%)

# Cleanup temporary graph files
rm -f graph_*.txt

echo "All tests completed successfully. Results are saved in the results directory." 