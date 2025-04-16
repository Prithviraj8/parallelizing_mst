CXX = g++
CXXFLAGS = -std=c++14 -O3 -I./header

SRCS = main_sequential.cpp main/prims_sequential.cpp main/kruskals_sequential.cpp main/sequential_sort.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = ../sequential_mst

all: $(TARGET)

sequential_mst: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

.PHONY: all clean sequential_mst