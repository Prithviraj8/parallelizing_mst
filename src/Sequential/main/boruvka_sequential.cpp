#include "../header/boruvka_sequential.h"
#include <algorithm>

// Constructor
BoruvkaGraph::BoruvkaGraph(int vertices) 
    : V(vertices), 
      graph(), 
      Parent() {}

// Graph Operations
void BoruvkaGraph::EnterEdges(int& u, int& v, int& w) {
    graph.push_back({u, v, w});
}

// Union-Find Operations
int BoruvkaGraph::findParent(vector<int>& parent, int i) {
    while (i != parent[i]) i = parent[i];
    return i;
}

void BoruvkaGraph::unionSet(vector<int>& parent, vector<int>& rank, int& x_parent, int& y_parent) {
    if (rank[x_parent] < rank[y_parent]) {
        parent[x_parent] = y_parent;
    } else if (rank[y_parent] < rank[x_parent]) {
        parent[y_parent] = x_parent;
    } else {
        parent[y_parent] = x_parent;
        rank[x_parent]++;
    }
}

// MST Algorithm
void BoruvkaGraph::BoruvkaMST() {
    // Initialize data structures
    vector<int> parent(V);
    vector<int> rank(V, 0);
    vector<vector<int>> cheapest(V, vector<int>(3, -1));
    
    // Initialize parent array
    for (int i = 0; i < V; i++) parent[i] = i;

    int MSTweight = 0;
    int numTrees = V;

    // Main algorithm loop
    while (numTrees > 1) {
        // Find cheapest edges for each component
        for (const auto& edge : graph) {
            int u = edge[0], v = edge[1], w = edge[2];
            int parent_u = findParent(parent, u);
            int parent_v = findParent(parent, v);

            if (parent_u != parent_v) {
                if (cheapest[parent_u][2] == -1 || cheapest[parent_u][2] > w) 
                    cheapest[parent_u] = {u, v, w};
                if (cheapest[parent_v][2] == -1 || cheapest[parent_v][2] > w) 
                    cheapest[parent_v] = {u, v, w};
            }
        }

        // Add cheapest edges to MST
        for (int node = 0; node < V; node++) {
            if (cheapest[node][2] != -1) {
                int u = cheapest[node][0], v = cheapest[node][1], w = cheapest[node][2];
                int parent_u = findParent(parent, u);
                int parent_v = findParent(parent, v);

                if (parent_u != parent_v) {
                    MSTweight += w;
                    unionSet(parent, rank, parent_u, parent_v);
                    Parent.push_back({u, v, w});
                    numTrees--;
                }
            }
        }

        // Reset cheapest edges for next iteration
        fill(cheapest.begin(), cheapest.end(), vector<int>(3, -1));
    }

    printf("Weight of MST is %d\n", MSTweight);
}

// Output Operations
void BoruvkaGraph::PrintBoruvkaMST() {
    printf("Edge \tWeight\n");
    for (const auto& edge : Parent) {
        printf("%d - %d \t%d\n", edge[0], edge[1], edge[2]);
    }
}
