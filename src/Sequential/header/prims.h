#ifndef PRIMS_SEQUENTIAL_H
#define PRIMS_SEQUENTIAL_H

#include <vector>
#include <iostream>
#include <climits>
#include <stdexcept>
#include <sort.h>

using namespace std;

class PrimsGraph {
private:
    const int selection;
    const int Vertices;
    
    // Graph representation
    vector<vector<int>> graph;    // Adjacency matrix
    vector<int> parent;           // Parent nodes in MST
    vector<int> key;             // Key values used to pick minimum weight edge
    vector<bool> MSTset;         // Track vertices included in MST

public:
    // Constructor
    PrimsGraph(int V, int s);

    // Graph operations
    void EnterEdges(int& u, int& v, int& w);
    
    // MST operations
    pair<int,int> FindNextMin() const;
    void PrimMST();
    void PrintPrimsMST() const;
};

#endif // PRIMS_SEQUENTIAL_H