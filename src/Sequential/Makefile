CXX = g++
CXXFLAGS = -std=c++14 -O3 -I./header

SRCS = main.cpp main/prims.cpp main/kruskals.cpp main/sort.cpp
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