#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>
#include <chrono>
#include <cstdlib>
#include <boruvka_sequential.h>

using namespace std;

// Function to parse the input text file and store edges in a vector
void parseEdges(const string& filename, vector<tuple<int, int, int>>& edges) {
    ifstream file(filename);  // Open the file

    if (!file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);  // Create a stringstream for the current line
        int u, v, w;
        ss >> u >> v >> w;  // Read u, v, w from the line

        // Add the edge (u, v, w) to the edges vector
        edges.push_back(make_tuple(u, v, w));
    }

    file.close();  // Close the file
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("./test_boruvka <vertices> <edges> <selection> <edges_file>\n");
        exit(0);
    }

    string ifile = "";
    int vertices = 0;
    int edge = 0;
    int selection = 1;

    vertices = atoi(argv[1]);
    edge = atoi(argv[2]);
    selection = atoi(argv[3]);
    ifile += argv[4];

    vector<tuple<int,int,int>> edges;
    parseEdges(ifile, edges);

    // Declare graph for Boruvka's method
    BoruvkaGraph* g_b = new BoruvkaGraph(vertices);

    // Add edges to graph
    for (const auto& edge : edges) {
        int u, v, w;
        tie(u, v, w) = edge;  // Extract u, v, w from the tuple
        g_b -> EnterEdges(u, v, w);
    }

    // Get the start time
    auto start = std::chrono::high_resolution_clock::now();

    // Run Boruvka's MST algorithm
    g_b -> BoruvkaMST();

    // Get the end time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time in seconds
    std::chrono::duration<double> elapsed = end - start;
    printf("Elapsed time for Boruvka's Sequential MST calculation for %d vertices, %d edges: %lf seconds\n", 
           vertices, edge, elapsed.count());

    // Print the MST
    g_b -> PrintBoruvkaMST();

    // Free memory
    delete g_b;

    return 0;
} 