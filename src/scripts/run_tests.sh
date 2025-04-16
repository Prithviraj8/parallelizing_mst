#!/bin/bash

# Exit on any error
set -e

# Create results directory if it doesn't exist
mkdir -p results

# Compile parallel implementation
echo "=== Compiling parallel implementation ==="
cd Parallel && make clean && make && cd ..

# Function to run tests for a specific configuration
run_test() {
    local V=$1
    local E=$2
    
    echo "=== Testing configuration: $V vertices, $E edges ==="
    echo "Generating graph..."
    
    # Generate graph
    ./edges $V $E "input.txt"
    echo ""
    
    # Test with different sorting methods
    for sort_method in 1 2 3; do
        echo -e "\n=== Using sorting method $sort_method ==="
        
        # Test with different thread counts
        for threads in 1 2 4 8; do
            echo "Testing with $threads thread(s):"
            
            # Run parallel implementation
            ./parallel_mst $threads $V $E $sort_method "input.txt"
            echo -e "\n"
        done
    done
    
    echo "Completed testing for $V vertices, $E edges"
    echo -e "\n----------------------------------------"
}

# Test configurations
run_test 100 4000     # Small case
run_test 1000 20000   # Medium case
run_test 1500 50000   # Large case

# Cleanup
rm -f input.txt

echo "All tests completed. Results are saved in the results directory." 