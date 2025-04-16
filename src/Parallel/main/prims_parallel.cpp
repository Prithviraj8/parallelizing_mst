#include <prims_parallel.h>

PrimsGraph_p::PrimsGraph_p(int V, int s, int n)
    : NUMTHREADS(n), selection(s), Vertices(V) {
    graph.assign(V, std::vector<int>(V, 0));
    parent.assign(V, -1);
    key.assign(V, INT_MAX);
    MSTset.assign(V, false);
}

void PrimsGraph_p::EnterEdges(int& u, int& v, int& w) {
    if (u >= 0 && u < Vertices && v >= 0 && v < Vertices) {
        graph[u][v] = w;
        graph[v][u] = w;  // Undirected graph
    }
}

std::pair<int, int> PrimsGraph_p::FindNextMin() {
    const int length = key.size();
    const int work = std::ceil((float)length / (float)NUMTHREADS);
    std::vector<std::vector<int>> Thread_values(NUMTHREADS);

    // Parallel section to find local minimums
    #pragma omp parallel num_threads(NUMTHREADS)
    {
        const int tid = omp_get_thread_num();
        const int start = tid * work;
        const int end = std::min(start + work, length);
        int priv_min = INT_MAX;
        int priv_idx = -1;

        // Find local minimum for this thread's section
        for (int i = start; i < end; i++) {
            if (!MSTset[i] && key[i] < priv_min) {
                priv_min = key[i];
                priv_idx = i;
            }
        }
        Thread_values[tid] = {priv_min, priv_idx};
    }

    // Sort thread values to find global minimum
    try {
        switch(selection) {
            case 1:  // Bubble Sort
                parallelBubbleSort(Thread_values, NUMTHREADS);
                break;

            case 2:  // Quick Sort
                parallelQuickSort(Thread_values, NUMTHREADS);
                break;

            case 3:  // Merge Sort
                parallelMergeSort(Thread_values, NUMTHREADS);
                break;

            default:
                throw std::invalid_argument("Invalid sorting algorithm selection. Choose 1 (Bubble), 2 (Quick), or 3 (Merge).");
        }
    }
    catch (const std::exception& e) {
        printf("Error in sorting thread values: %s\n", e.what());
        return std::make_pair(-1, INT_MAX);  // Return invalid values to indicate error
    }

    // Return the minimum value and its index
    return std::make_pair(Thread_values[0][1], Thread_values[0][0]);
}

void PrimsGraph_p::PrimMST() {
    try {
        // Initialize MST with first vertex
        key[0] = 0;
        parent[0] = -1;
        int MSTweight = 0;
        int edgesInMST = 0;

        // Main MST construction loop
        for (int count = 0; count < Vertices; count++) {
            // Find next minimum key vertex
            std::pair<int, int> p = FindNextMin();
            int u = p.first;
            int w = p.second;
            
            if (u == -1 || w == INT_MAX) {
                throw std::runtime_error("Error finding next minimum vertex");
            }

            MSTset[u] = true;  // Add to MST
            MSTweight += w;
            edgesInMST++;

            // Update adjacent vertices' keys
            #pragma omp parallel num_threads(NUMTHREADS)
            {
                #pragma omp for
                for (int v = 0; v < Vertices; v++) {
                    // Update key if:
                    // 1. There is an edge from u to v
                    // 2. v is not in MST
                    // 3. Edge weight is less than current key
                    if (graph[u][v] && !MSTset[v] && graph[u][v] < key[v]) {
                        #pragma omp critical
                        {
                            parent[v] = u;
                            key[v] = graph[u][v];
                        }
                    }
                }
            }
        }

        if (edgesInMST != Vertices) {
            throw std::runtime_error("Could not construct a complete MST. Graph might be disconnected.");
        }

        printf("Weight of MST is %d\n", MSTweight);
    }
    catch (const std::exception& e) {
        printf("Error in PrimMST: %s\n", e.what());
    }
}

void PrimsGraph_p::PrintPrimsMST() const {
    if (std::count(parent.begin(), parent.end(), -1) == Vertices) {
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
