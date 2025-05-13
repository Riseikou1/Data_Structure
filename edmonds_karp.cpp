#include <iostream>
#include <vector>
#include <queue>
#include <climits>  // For INT_MAX
#include <algorithm> // For reverse

using namespace std;

class Graph {
    int size;
    vector<vector<int>> adj_matrix;
    vector<string> vertex_data;

public:
    Graph(int n) : size(n), adj_matrix(n, vector<int>(n, 0)), vertex_data(n, "") {}

    void add_edge(const int u, const int v, const int capacity) {
        adj_matrix[u][v] = capacity;
    }

    void add_vertex_data(const int vertex, const string& data) {
        if (vertex >= 0 && vertex < size) {
            vertex_data[vertex] = data;
        }
    }

    bool bfs(const int source, const int sink, vector<int>& parent) const  {
        vector<bool> visited(size, false);
        queue<int> q;

        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < size; ++v) {
                if (!visited[v] && adj_matrix[u][v] > 0) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;

                    if (v == sink)
                        return true;
                }
            }
        }

        return false;
    }

    int edmonds_karp(const int source, const int sink) {
        vector<int> parent(size);
        int max_flow = 0;

        cout << string(45, '*') << endl;
        cout << "Augmenting Paths Found:\n";

        while (bfs(source, sink, parent)) {
            int path_flow = INT_MAX;

            // Find minimum residual capacity in the path
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                path_flow = min(path_flow, adj_matrix[u][v]);
            }

            // Update residual capacities
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                adj_matrix[u][v] -= path_flow;
                adj_matrix[v][u] += path_flow;
            }

            max_flow += path_flow;

            // Print the path
            vector<string> path;
            for (int v = sink; v != -1; v = parent[v])
                path.push_back(vertex_data[v]);

            reverse(path.begin(), path.end());

            cout << "Path : ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i != path.size() - 1)
                    cout << " -> ";
            }
            cout << "  || Flow : " << path_flow << endl;
        }

        cout << string(45, '*') << endl;
        return max_flow;
    }
};

int main() {
    Graph g(6);
    vector<string> names = {"s", "v1", "v2", "v3", "v4", "t"};
    for (int i = 0; i < 6; ++i)
        g.add_vertex_data(i, names[i]);

    g.add_edge(0, 1, 3);  // s -> v1
    g.add_edge(0, 2, 7);  // s -> v2
    g.add_edge(1, 3, 3);  // v1 -> v3
    g.add_edge(1, 4, 4);  // v1 -> v4
    g.add_edge(2, 1, 5);  // v2 -> v1
    g.add_edge(2, 4, 3);  // v2 -> v4
    g.add_edge(3, 4, 3);  // v3 -> v4
    g.add_edge(3, 5, 2);  // v3 -> t
    g.add_edge(4, 5, 6);  // v4 -> t


    int max_flow = g.edmonds_karp(0, 5);  // s to t
    cout << "The maximum possible flow is: " << max_flow << endl;
    cout << string(45, '*') << endl;

    return 0;
}
