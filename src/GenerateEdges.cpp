#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: ./genEdge <vertices> <edges> <filename.txt>" << endl;
        return 1;
    }

    int V = atoi(argv[1]);  // Number of vertices
    int E = atoi(argv[2]);  // Number of edges
    string filename = argv[3];

    // Check if E exceeds maximum possible edges
    int maxEdges = V * (V - 1) / 2;
    if (E > maxEdges) {
        cout << "Error: Number of edges exceeds maximum possible edges for " << V << " vertices." << endl;
        cout << "Maximum possible edges: " << maxEdges << endl;
        return 1;
    }

    // Generate all possible edges
    vector<pair<int, int> > allEdges;
    for (int u = 0; u < V; u++) {
        for (int v = u + 1; v < V; v++) {
            allEdges.push_back(make_pair(u, v));
        }
    }

    // Shuffle edges randomly
    random_device rd;
    mt19937 gen(rd());
    shuffle(allEdges.begin(), allEdges.end(), gen);

    // Open file for writing
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Error: Could not open file for writing!" << endl;
        return 1;
    }

    // Write first E edges with random weights
    uniform_int_distribution<> weightDist(1, 100);
    for (int i = 0; i < E; i++) {
        int weight = weightDist(gen);
        outFile << allEdges[i].first << " " << allEdges[i].second << " " << weight << endl;
    }

    outFile.close();
    cout << "Generated graph with " << V << " vertices and " << E << " edges" << endl;

    return 0;
}