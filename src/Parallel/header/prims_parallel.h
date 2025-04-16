#ifndef PRIMS_PARALLEL_H
#define PRIMS_PARALLEL_H

#include <bits/stdc++.h>
#include <omp.h>
#include <parallel/algorithm>
#include <parallel_sort.h>
#include <cmath>
#include <stdexcept>

class PrimsGraph_p {
private:
    const int NUMTHREADS;
    const int selection;
    const int Vertices;
    
    std::vector<std::vector<int>> graph;
    std::vector<int> parent;
    std::vector<int> key;
    std::vector<bool> MSTset;

public:
    PrimsGraph_p(int V, int s, int n);

    void EnterEdges(int& u, int& v, int& w);
    std::pair<int, int> FindNextMin();
    void PrimMST();
    void PrintPrimsMST() const;
};

#endif // PRIMS_PARALLEL_H