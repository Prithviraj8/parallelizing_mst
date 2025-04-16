#include <kruskals_sequential.h>

UnionSet::UnionSet(int n) : size(n) {
    if (n <= 0) {
        throw invalid_argument("Size must be positive");
    }
    parent = make_unique<int[]>(n);
    rank = make_unique<int[]>(n);

    for (int i = 0; i < n; i++) {
        parent[i] = i;    // Each node is its own parent initially
        rank[i] = 1;      // Initial rank is 1
    }
}

int UnionSet::findParent(int node) {
    if (node < 0 || node >= size) {
        throw out_of_range("Node index out of range");
    }
    
    if (parent[node] == node) {
        return node;
    }
    
    // Path compression: make the parent of all nodes in path point to root
    return parent[node] = findParent(parent[node]);
}

void UnionSet::Union(int& u, int& v) {
    if (u < 0 || u >= size || v < 0 || v >= size) {
        throw out_of_range("Node indices out of range");
    }

    int u_parent = findParent(u);
    int v_parent = findParent(v);

    if (u_parent == v_parent) {
        return;  // Already in same set
    }   

    // Union by rank: attach smaller rank tree under root of higher rank tree
    if (rank[u_parent] > rank[v_parent]) {
        parent[v_parent] = u_parent;
    }
    else if (rank[u_parent] < rank[v_parent]) {
        parent[u_parent] = v_parent;
    }
    else {
        parent[v_parent] = u_parent;
        rank[u_parent]++;  // Increase rank when same
    }
}

KruskalsGraph::KruskalsGraph(int V, int s) 
    : selection(s), Vertices(V) {
    if (V <= 0) {
        throw invalid_argument("Number of vertices must be positive");
    }
    edgeList.reserve(V * (V - 1) / 2);  // Maximum possible edges in undirected graph
}

void KruskalsGraph::EnterEdges(int& u, int& v, int& w) {
    if (u < 0 || u >= Vertices || v < 0 || v >= Vertices) {
        throw out_of_range("Vertex indices out of range");
    }
    edgeList.push_back({w, u, v});
}

void KruskalsGraph::SortList() {
    try {
        switch(selection) {
            case 1:  // Bubble Sort
                SequentialBubbleSort(edgeList);
                break;

            case 2: {  // Quick Sort
                int length = edgeList.size();
                SequentialQuickSort(edgeList, 0, length - 1);
                break;
            }

            case 3: {  // Merge Sort
                int length = edgeList.size();
                SequentialMergeSort(edgeList, 0, length - 1);
                break;
            }

            default:
                throw invalid_argument("Please select a valid sorting algorithm (1: Bubble, 2: Quick, 3: Merge)");
        }
    }
    catch (const exception& e) {
        printf("Error in sorting: %s\n", e.what());
        throw;  // Re-throw to be handled by caller
    }
}

void KruskalsGraph::KruskalMST() {
    try {
        SortList();
        
        auto dsu = make_unique<UnionSet>(Vertices);
        int MSTweight = 0;
        int edgesInMST = 0;

        for (const auto& edge : edgeList) {
            int w = edge[0], u = edge[1], v = edge[2];
            
            // Check if including this edge creates a cycle
            if (dsu->findParent(u) != dsu->findParent(v)) {
                dsu->Union(u, v);
                MSTweight += w;
                Parent.push_back({u, v, w});
                edgesInMST++;
            }
        }

        // Check if we have a valid MST
        if (edgesInMST != Vertices - 1) {
            throw runtime_error("Could not construct a complete MST. Graph might be disconnected.");
        }

        printf("Weight of MST is %d\n", MSTweight);
    }
    catch (const exception& e) {
        printf("Error in KruskalMST: %s\n", e.what());
    }
}

void KruskalsGraph::PrintKruskalsMST() const {
    if (Parent.empty()) {
        printf("MST has not been computed yet.\n");
        return;
    }

    printf("Edge \tWeight\n");
    for (const auto& p : Parent) {
        printf("%d - %d \t%d\n", p[0], p[1], p[2]);
    }
}
