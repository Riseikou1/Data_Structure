#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
    int size;
    vector<vector<int>> adj_matrix;
    vector<string> vertex_data;

public:
    Graph(int size) : size(size), adj_matrix(size, vector<int>(size, 0)), vertex_data(size, "") {}

    void add_vertex_data(int vertex, const string& data) {
        if (vertex >= 0 && vertex < size) {
            vertex_data[vertex] = data;
        }
    }

    void add_edge(int u, int v, int weight) {
        if (u >= 0 && u < size && v >= 0 && v < size) {
            adj_matrix[u][v] = weight;
            adj_matrix[v][u] = weight; // Undirected
        }
    }

    void prims_algorithm() {
        vector<int> key(size, INT_MAX);
        vector<int> parent(size, -1);
        vector<bool> in_mst(size, false);

        key[0] = 0;

        for (int count = 0; count < size; ++count) {
            // Find the minimum key vertex not yet included in MST
            int u = -1;
            int min_key = INT_MAX;
            for (int v = 0; v < size; ++v) {
                if (!in_mst[v] && key[v] < min_key) {
                    min_key = key[v];
                    u = v;
                }
            }

            if (u == -1) break; // disconnected graph
            in_mst[u] = true;

            // Update key and parent of adjacent vertices
            for (int v = 0; v < size; ++v) {
                int weight = adj_matrix[u][v];
                if (weight && !in_mst[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }

        cout << string(40, '*') << "\nPrim's Algorithm - Minimum Spanning Tree:\n" << string(40, '*') << endl;
        cout << "Edge\tWeight" << endl;
        int total_weight = 0;
        for (int v = 1; v < size; ++v) {
            int u = parent[v];
            int weight = adj_matrix[u][v];
            cout << vertex_data[u] << " - " << vertex_data[v] << "\t" << weight << endl;
            total_weight += weight;
        }
        cout << "Total Weight of MST : " << total_weight << endl;
    }
};

int main() {
    Graph g(8);
    vector<string> labels = {"A", "B", "C", "D", "E", "F", "G", "H"};

    for (int i = 0; i < labels.size(); ++i) {
        g.add_vertex_data(i, labels[i]);
    }

    vector<tuple<int, int, int>> edges = {
        {0, 1, 4}, {0, 3, 3}, {1, 2, 3}, {1, 3, 5}, {1, 4, 6},
        {2, 4, 4}, {2, 7, 2}, {3, 4, 7}, {3, 5, 4},
        {4, 5, 5}, {4, 6, 3}, {5, 6, 7}, {6, 7, 5}
    };

    for (const auto& [u, v, w] : edges) {
        g.add_edge(u, v, w);
    }

    g.prims_algorithm();

    return 0;
}
