#ifndef KRUSKALS_SEQUENTIAL_H
#define KRUSKALS_SEQUENTIAL_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <memory>
#include <stdexcept>
#include <sequential_sort.h>

using namespace std;

class UnionSet {
private:
    unique_ptr<int[]> parent;
    unique_ptr<int[]> rank;
    const int size;

public:
    explicit UnionSet(int n);
    
    // Prevent copying
    UnionSet(const UnionSet&) = delete;
    UnionSet& operator=(const UnionSet&) = delete;

    int findParent(int node);
    void Union(int& u, int& v);
};

class KruskalsGraph {
private:
    const int selection;
    const int Vertices;
    vector<vector<int>> edgeList;  // {weight, u, v}
    vector<vector<int>> Parent;    // Store MST edges

public:
    KruskalsGraph(int V, int s);

    // Graph operations
    void EnterEdges(int& u, int& v, int& w);
    void SortList();

    // MST operations
    void KruskalMST();
    void PrintKruskalsMST() const;
};

#endif // KRUSKALS_SEQUENTIAL_H