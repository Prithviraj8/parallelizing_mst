CXX = g++
CXXFLAGS = -std=c++14 -O3 -I./header -I/usr/local/opt/libomp/include -Xpreprocessor -fopenmp
LDFLAGS = -L/usr/local/opt/libomp/lib -lomp

SRCS = main.cpp main/prims.cpp main/kruskals.cpp main/sort.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = ../parallel_mst

all: $(TARGET)

parallel_mst: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

.PHONY: all clean parallel_mst
