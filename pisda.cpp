#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
    int size;
    vector<tuple<int, int, int>> edges;  // List of (u, v, weight)
    vector<string> vertex_data;  // Human-readable vertex labels

public:
    Graph(int size) : size(size), vertex_data(size, "") {}

    void add_edge(const int u, const int v, const int weight) {
        if (0 <= u && u < size && 0 <= v && v < size) {
            edges.push_back(make_tuple(u, v, weight));
        }
    }

    void add_vertex_data(int vertex, const string& data) {
        if (0 <= vertex && vertex < size) {
            vertex_data[vertex] = data;
        }
    }

    int find(vector<int>& parent, int i) {
        // Path compression
        if (parent[i] != i) {
            parent[i] = find(parent, parent[i]);
        }
        return parent[i];
    }

    void union_sets(vector<int>& parent, vector<int>& rank,const int x, const int y) {
        int xroot = find(parent, x);
        int yroot = find(parent, y);

        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        } else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    void kruskals_algorithm() {
        vector<tuple<int, int, int>> result;  // Store MST edges

        // Step 1: Sort edges by weight
        sort(edges.begin(), edges.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
            return get<2>(a) < get<2>(b);
        });

        // Step 2: Create disjoint sets
        vector<int> parent(size);
        vector<int> rank(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }

        for (const auto& edge : edges) {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int weight = get<2>(edge);

            int root_u = find(parent, u);
            int root_v = find(parent, v);

            if (root_u != root_v) {
                result.push_back(edge);
                union_sets(parent, rank, root_u, root_v);
            }
        }

        // Print MST
        cout << "Edge\tWeight\n";
        for (const auto& edge : result) {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int weight = get<2>(edge);
            cout << vertex_data[u] << "-" << vertex_data[v] << " \t " << weight << endl;
        }
    }
};

int main() {
    Graph g(7);
    vector<string> labels = {"A", "B", "C", "D", "E", "F", "G"};
    for (int i = 0; i < labels.size(); ++i) {
        g.add_vertex_data(i, labels[i]);
    }

    g.add_edge(0, 1, 4);   // A-B
    g.add_edge(0, 6, 10);  // A-G
    g.add_edge(0, 2, 9);   // A-C
    g.add_edge(1, 2, 8);   // B-C
    g.add_edge(2, 3, 5);   // C-D
    g.add_edge(2, 4, 2);   // C-E
    g.add_edge(2, 6, 7);   // C-G
    g.add_edge(3, 4, 3);   // D-E
    g.add_edge(3, 5, 7);   // D-F
    g.add_edge(4, 6, 6);   // E-G
    g.add_edge(5, 6, 11);  // F-G

    cout << string(44, '*') << "\nKruskal's Algorithm - Minimum Spanning Tree:\n" << string(44, '*') << endl;

    g.kruskals_algorithm();

    return 0;
}





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
