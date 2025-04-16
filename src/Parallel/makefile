CC = gcc
CFLAGS = -I./header -g -Wall -std=c11
# OpenMP enabled with macOS-compatible flags

CXX = g++
CXXFLAGS = -I./header -I/usr/local/opt/libomp/include -g -Wall -std=c++11 -Xpreprocessor -fopenmp
LDFLAGS = -L/usr/local/opt/libomp/lib -lomp

SRC_DIR = main
OBJ_DIR = obj

# List of object files
OBJS = $(OBJ_DIR)/main_parallel.o $(OBJ_DIR)/parallel_sort.o $(OBJ_DIR)/prims_parallel.o $(OBJ_DIR)/kruskals_parallel.o

# Ensure the object directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# The target for compiling the final program
parallel: $(OBJ_DIR) $(OBJS)
	$(CXX) -o ../parallel_mst $(OBJS) $(CXXFLAGS) $(LDFLAGS)

# Rule for compiling .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/main_parallel.o: $(SRC_DIR)/main_parallel.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

# Clean up the generated files
clean:
	rm -f $(OBJ_DIR)/*.o *~
	rm -rf $(OBJ_DIR)
	rm -f ../parallel_mst
	test ! -d ../parallel_mst || echo "Warning: ../parallel_mst is a directory"
