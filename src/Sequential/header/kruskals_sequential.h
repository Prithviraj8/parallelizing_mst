#ifndef KRUSKALS_SEQUENTIAL_H
#define KRUSKALS_SEQUENTIAL_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <sequential_sort.h>

using namespace std;

class UnionSet {
    int* parent;
    int* rank;

public:
    UnionSet(int n);

    int findParent(int);

    void Union(int&, int&);
};

class KruskalsGraph {
    int selection;
    vector<vector<int>> edgeList;
    vector<vector<int>> Parent;

    int Vertices;

public:
    KruskalsGraph(int V, int s);

    void EnterEdges(int&, int&, int&);

    void SortList();

    void KruskalMST();

    void PrintKruskalsMST();
};

#endif // KRUSKALS_SEQUENTIAL_H