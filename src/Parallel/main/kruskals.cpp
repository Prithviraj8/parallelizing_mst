#include <kruskals.h>

// UnionSet_p Implementation
UnionSet_p::UnionSet_p(int n) {
    parent = new int[n];
    rank = new int[n];

    #pragma omp parallel for
    for(int i = 0; i < n; i++) {
        parent[i] = i;  // Initialize each node as its own parent
        rank[i] = 1;    // Initialize rank as 1
    }
}

UnionSet_p::~UnionSet_p() {
    delete[] parent;
    delete[] rank;
}

int UnionSet_p::findParent(int node) {
    if (parent[node] == node) {
        return node;
    }
    // Path compression: Set each node's parent to the root
    return parent[node] = findParent(parent[node]);
}

void UnionSet_p::Union(int& u, int& v) {
    int u_parent = findParent(u);
    int v_parent = findParent(v);

    if (u_parent == v_parent) {
        return;  // Already in same set
    }   

    // Union by rank: Attach smaller rank tree under root of higher rank tree
    int u_rank = rank[u_parent];
    int v_rank = rank[v_parent];

    if (u_rank > v_rank) {
        parent[v_parent] = u_parent;
    }
    else if (u_rank < v_rank) {
        parent[u_parent] = v_parent;
    }
    else {
        parent[v_parent] = u_parent;
        rank[u_parent]++;  // Increment rank when equal
    }
}

// KruskalsGraph_p Implementation
KruskalsGraph_p::KruskalsGraph_p(int V, int s, int n) 
    : NUMTHREADS(n), selection(s), Vertices(V) {
    Parent.reserve(V-1);     // Reserve space for MST edges
    edgeList.reserve(V*V);   // Reserve space for potential edges
}

void KruskalsGraph_p::EnterEdges(int& u, int& v, int& w) {
    edgeList.push_back({w, u, v});  // Store edge with weight first for easier sorting
}

void KruskalsGraph_p::SortList() {
    if (edgeList.empty()) {
        return;
    }

    switch(selection) {
        case 1:  // Bubble Sort
            parallelBubbleSort(edgeList, NUMTHREADS);
            break;

        case 2:  // Quick Sort
            parallelQuickSort(edgeList, NUMTHREADS);
            break;

        case 3:  // Merge Sort
            parallelMergeSort(edgeList, NUMTHREADS);
            break;

        default:
            throw std::invalid_argument("Invalid sorting algorithm selection. Choose 1 (Bubble), 2 (Quick), or 3 (Merge).");
    }
}

void KruskalsGraph_p::KruskalMST() {
    try {
        SortList();

        std::unique_ptr<UnionSet_p> DSU(new UnionSet_p(Vertices));
        int MSTweight = 0;
        Parent.clear();  // Clear any existing MST edges

        for (const auto& edge : edgeList) {
            int w = edge[0], u = edge[1], v = edge[2];
            
            // Check if adding this edge creates a cycle
            int u_parent = DSU->findParent(u);
            int v_parent = DSU->findParent(v);

            if (u_parent != v_parent) {
                DSU->Union(u, v);
                MSTweight += w;
                Parent.push_back({u, v, w});
            }

            // Early exit if we have V-1 edges (complete MST)
            if (Parent.size() == Vertices - 1) {
                break;
            }
        }

        if (Parent.size() != Vertices - 1) {
            throw std::runtime_error("Could not construct a complete MST. Graph might be disconnected.");
        }

        printf("Weight of MST is %d\n", MSTweight);
    }
    catch (const std::exception& e) {
        printf("Error in KruskalMST: %s\n", e.what());
    }
}

void KruskalsGraph_p::PrintKruskalMST() const {
    if (Parent.empty()) {
        printf("MST has not been computed yet.\n");
        return;
    }

    printf("Edge \tWeight\n");
    for (const auto& edge : Parent) {
        printf("%d - %d \t%d\n", edge[0], edge[1], edge[2]);
    }
}