#ifndef KRUSKALS_PARALLEL_H
#define KRUSKALS_PARALLEL_H

#include <bits/stdc++.h>
#include <omp.h>
#include <parallel/algorithm>
#include <parallel_sort.h>
#include <cmath>
#include <memory>
#include <stdexcept>

using namespace std;

class UnionSet_p {
private:
    int* parent;
    int* rank;

public:
    explicit UnionSet_p(int n);
    ~UnionSet_p();
    
    // Prevent copying
    UnionSet_p(const UnionSet_p&) = delete;
    UnionSet_p& operator=(const UnionSet_p&) = delete;

    int findParent(int node);
    void Union(int& u, int& v);
};

class KruskalsGraph_p {
private:
    const int NUMTHREADS;
    const int selection;
    const int Vertices;
    std::vector<std::vector<int>> edgeList;
    std::vector<std::vector<int>> Parent;

public:
    KruskalsGraph_p(int V, int s, int n);

    void EnterEdges(int& u, int& v, int& w);
    void SortList();
    void KruskalMST();
    void PrintKruskalMST() const;
};

#endif // KRUSKALS_PARALLEL_H