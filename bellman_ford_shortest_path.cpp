#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

class Graph {
private:
    int size;
    vector<vector<int>> adj_matrix;
    vector<string> vertex_data;

public:
    Graph(int size) : size(size), adj_matrix(size, vector<int>(size, 0)), vertex_data(size, "") {}

    void add_edge(int v, int u, int weight) {
        if (u >= 0 && u < size && v >= 0 && v < size) {
            adj_matrix[u][v] = weight;
        }
    }

    void add_vertex_data(int vertex, const string& data) {
        if (vertex < size && vertex >= 0) {
            vertex_data[vertex] = data;
        }
    }

    tuple<bool, vector<int>, vector<int>> bellman_ford(const string& start_vertex_data, vector<int>& distances, vector<int>& predecessors) {
        int start_vertex = find(vertex_data.begin(), vertex_data.end(), start_vertex_data) - vertex_data.begin();
        distances.assign(size, numeric_limits<int>::infinity());
        predecessors.assign(size, -1);
        distances[start_vertex] = 0;

        for (int i = 0; i < size - 1; i++) {
            bool updated = false;
            for (int u = 0; u < size; u++) {
                for (int v = 0; v < size; v++) {
                    if (adj_matrix[u][v] != 0) {
                        int new_dist = adj_matrix[u][v] + distances[u];
                        if (new_dist < distances[v]) {
                            distances[v] = new_dist;
                            predecessors[v] = u;
                            updated = true;
                        }
                    }
                }
            }
            if (!updated) {
                break;
            }
        }

        for (int u = 0; u < size; u++) {
            for (int v = 0; v < size; v++) {
                if (adj_matrix[u][v] != 0 && distances[u] + adj_matrix[u][v] < distances[v]) {
                    return {true, {}, {}};  // Negative cycle detected
                }
            }
        }

        return {false, distances, predecessors};
    }

    string get_path(const string& start_vertex_data, const string& end_vertex_data, vector<int>& predecessors) {
        int start_vertex = find(vertex_data.begin(), vertex_data.end(), start_vertex_data) - vertex_data.begin();
        int end_vertex = find(vertex_data.begin(), vertex_data.end(), end_vertex_data) - vertex_data.begin();

        vector<string> path;
        int current = end_vertex;

        while (current != -1) {
            path.insert(path.begin(), vertex_data[current]);
            current = predecessors[current];
            if (current == start_vertex) {
                path.insert(path.begin(), vertex_data[start_vertex]);
                break;
            }
        }

        string path_str;
        for (const auto& vertex : path) {
            path_str += vertex + "->";
        }

        if (!path_str.empty()) {
            path_str.pop_back(); // Remove the last '->'
        }

        return path_str;
    }
};

int main() {
    Graph g(5);

    // Add vertices with labels
    g.add_vertex_data(0, "A");
    g.add_vertex_data(1, "B");
    g.add_vertex_data(2, "C");
    g.add_vertex_data(3, "D");
    g.add_vertex_data(4, "E");

    // Add directed edges with weights
    g.add_edge(3, 0, 4);  // D -> A, weight 4
    g.add_edge(3, 2, 7);  // D -> C, weight 7
    g.add_edge(3, 4, 3);  // D -> E, weight 3
    g.add_edge(0, 2, 4);  // A -> C, weight 4
    g.add_edge(2, 0, -3); // C -> A, weight -3
    g.add_edge(0, 4, 5);  // A -> E, weight 5
    g.add_edge(4, 2, 3);  // E -> C, weight 3
    g.add_edge(1, 2, -4); // B -> C, weight -4
    g.add_edge(4, 1, 2);  // E -> B, weight 2

    vector<int> distances, predecessors;
    auto [negative_cycle, distances_result, predecessors_result] = g.bellman_ford("D", distances, predecessors);

    if (!negative_cycle) {
        for (int i = 0; i < distances_result.size(); i++) {
            if (distances_result[i] != numeric_limits<int>::infinity()) {
                string path = g.get_path("D", g.vertex_data[i], predecessors_result);
                cout << "Shortest path from D to " << g.vertex_data[i] << ": " << path << ", Distance: " << distances_result[i] << endl;
            } else {
                cout << "No path from D to " << g.vertex_data[i] << ", Distance: Infinity" << endl;
            }
        }
    } else {
        cout << "Negative weight cycle detected. Cannot compute shortest paths." << endl;
    }

    return 0;
}
