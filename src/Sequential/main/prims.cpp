#include <prims.h>

PrimsGraph::PrimsGraph(int V, int s)
    : selection(s), Vertices(V) {
    if (V <= 0) {
        throw invalid_argument("Number of vertices must be positive");
    }
    graph.assign(V, vector<int>(V, 0));
    parent.assign(V, -1);
    key.assign(V, INT_MAX);
    MSTset.assign(V, false);
}

void PrimsGraph::EnterEdges(int& u, int& v, int& w) {
    if (u < 0 || u >= Vertices || v < 0 || v >= Vertices) {
        throw out_of_range("Vertex indices out of range");
    }
    graph[u][v] = w;
    graph[v][u] = w;  // Undirected graph
}

pair<int,int> PrimsGraph::FindNextMin() const {
    int min = INT_MAX;
    int min_idx = -1;

    for (int v = 0; v < Vertices; v++) {
        if (!MSTset[v] && key[v] < min) { 
            min = key[v];
            min_idx = v;
        }
    }

    if (min_idx == -1) {
        throw runtime_error("No minimum vertex found. Graph might be disconnected.");
    }

    return make_pair(min_idx, min);
}

void PrimsGraph::PrimMST() {
    try {
        // Initialize MST with first vertex
        key[0] = 0;
        parent[0] = -1;
        int MSTweight = 0;
        int edgesInMST = 0;

        for (int count = 0; count < Vertices; count++) {
            // Find vertex with minimum key value
            pair<int,int> p = FindNextMin();
            int u = p.first;
            int w = p.second;

            MSTset[u] = true;  // Add to MST
            MSTweight += w;
            edgesInMST++;

            // Update key values of adjacent vertices
            for (int v = 0; v < Vertices; v++) {
                // Update key if:
                // 1. There is an edge from u to v
                // 2. v is not in MST
                // 3. Edge weight is less than current key
                if (graph[u][v] && !MSTset[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }

        if (edgesInMST != Vertices) {
            throw runtime_error("Could not construct a complete MST. Graph might be disconnected.");
        }

        printf("Weight of MST is %d\n", MSTweight);
    }
    catch (const exception& e) {
        printf("Error in PrimMST: %s\n", e.what());
    }
}

void PrimsGraph::PrintPrimsMST() const {
    if (count(parent.begin(), parent.end(), -1) == Vertices) {
        printf("MST has not been computed yet.\n");
        return;
    }

    printf("Edge \tWeight\n");
    for (int i = 1; i < Vertices; i++) {
        if (parent[i] != -1) {
            printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        }
    }
}
