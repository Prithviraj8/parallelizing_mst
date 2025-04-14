#!/bin/bash

# Function to run tests for a specific configuration
run_test() {
    local V=$1
    local E=$2
    
    echo "=== Testing configuration: $V vertices, $E edges ==="
    echo "Generating graph..."
    
    # Generate graph
    ./generate_large_graph $V $E "graph_${V}_${E}.txt"
    
    # Test with different sorting methods
    for sort_method in 1 2 3; do
        echo -e "\n=== Using sorting method $sort_method ==="
        
        # Run sequential implementation
        ./Sequential/sequential $V $E $sort_method "graph_${V}_${E}.txt"
        echo ""
    done
    
    echo "Completed testing for $V vertices, $E edges"
    echo -e "\n----------------------------------------"
}

# Compile everything first
echo "Compiling..."
cd Sequential && make clean && make sequential
cd ..
g++ -o generate_large_graph GenerateEdges.cpp

# Create results directory if it doesn't exist
mkdir -p results

# Test configurations
# Small graph
run_test 100 4000

# Medium graph
run_test 1000 20000

# Large graph
run_test 1500 50000

echo "All tests completed. Results are saved in the results directory." 