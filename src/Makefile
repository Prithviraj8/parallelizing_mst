CXX = g++
CXXFLAGS = -std=c++11 -Wall
PARALLEL_FLAGS = -fopenmp
INCLUDES = -I./Parallel/header -I./Sequential/header

# Default target
all: parallel sequential edges

# Parallel target
parallel:
	$(MAKE) -C Parallel

# Sequential target
sequential:
	$(MAKE) -C Sequential

# Edge generator
edges: generate_edges.cpp
	$(CXX) $(CXXFLAGS) -o edges generate_edges.cpp

# Clean all builds
clean:
	$(MAKE) -C Parallel clean
	$(MAKE) -C Sequential clean
	rm -f edges

.PHONY: all parallel sequential clean 