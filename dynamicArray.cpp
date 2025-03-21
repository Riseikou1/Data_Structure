#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Graph {
public:
    Graph(int size) {
        adj_matrix.resize(size, std::vector<int>(size, 0)); // Initialize adjacency matrix with 0
        vertex_data.resize(size, ""); // Vertex labels
        this->size = size;
    }

    void add_edge(int u, int v, int weight) {
        if (u >= 0 && u < size && v >= 0 && v < size) {
            adj_matrix[u][v] = weight; // Directed edge
        }
    }

    void add_vertex_data(int vertex, const std::string& data) {
        if (vertex >= 0 && vertex < size) {
            vertex_data[vertex] = data;
        }
    }

    std::tuple<bool, std::vector<int>, std::vector<int>> bellman_ford(const std::string& start_vertex_data) {
        int start_vertex = find_vertex_index(start_vertex_data);
        std::vector<int> distances(size, std::numeric_limits<int>::infinity()); // Initialize distances as infinity
        std::vector<int> predecessors(size, -1); // Predecessors to track paths
        distances[start_vertex] = 0; // Distance to start vertex is 0

        // Relax edges |V| - 1 times
        for (int i = 0; i < size - 1; ++i) {
            bool updated = false;
            for (int u = 0; u < size; ++u) {
                for (int v = 0; v < size; ++v) {
                    if (adj_matrix[u][v] != 0) { // If there's an edge from u to v
                        int new_dist = distances[u] + adj_matrix[u][v];
                        if (new_dist < distances[v]) { // Relax the edge
                            distances[v] = new_dist;
                            predecessors[v] = u;
                            updated = true;
                        }
                    }
                }
            }
            if (!updated) {
                break; // Stop early if no updates in this pass
            }
        }

        // Negative cycle detection (after all relaxations)
        for (int u = 0; u < size; ++u) {
            for (int v = 0; v < size; ++v) {
                if (adj_matrix[u][v] != 0 && distances[u] + adj_matrix[u][v] < distances[v]) {
                    return {true, {}, {}}; // Negative cycle detected
                }
            }
        }

        return {false, distances, predecessors};
    }

    std::string get_path(const std::vector<int>& predecessors, const std::string& start_vertex_data, const std::string& end_vertex_data) {
        int start_vertex = find_vertex_index(start_vertex_data);
        int end_vertex = find_vertex_index(end_vertex_data);

        std::vector<std::string> path;
        int current = end_vertex;
        while (current != -1) {
            path.insert(path.begin(), vertex_data[current]); // Insert at the beginning of the list
            current = predecessors[current];
            if (current == start_vertex) { // Stop when we reach the start vertex
                path.insert(path.begin(), vertex_data[start_vertex]);
                break;
            }
        }

        std::string path_str;
        for (const auto& vertex : path) {
            path_str += vertex + "->";
        }

        if (!path_str.empty()) {
            path_str.pop_back(); // Remove last '->'
        }

        return path_str;
    }

private:
    std::vector<std::vector<int>> adj_matrix; // Adjacency matrix
    std::vector<std::string> vertex_data;     // Vertex labels
    int size;

    int find_vertex_index(const std::string& vertex_data_str) {
        for (int i = 0; i < size; ++i) {
            if (vertex_data[i] == vertex_data_str) {
                return i;
            }
        }
        return -1; // Shouldn't happen if the vertex exists
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

    // Running the Bellman-Ford algorithm from D to all vertices
    std::cout << "\nThe Bellman-Ford Algorithm starting from vertex D:" << std::endl;
    auto [negative_cycle, distances, predecessors] = g.bellman_ford("D");

    if (!negative_cycle) {
        for (int i = 0; i < distances.size(); ++i) {
            if (distances[i] != std::numeric_limits<int>::infinity()) {
                std::string path = g.get_path(predecessors, "D", g.vertex_data[i]);
                std::cout << "Shortest path from D to " << g.vertex_data[i] << ": " << path << ", Distance: " << distances[i] << std::endl;
            } else {
                std::cout << "No path from D to " << g.vertex_data[i] << ", Distance: Infinity" << std::endl;
            }
        }
    } else {
        std::cout << "Negative weight cycle detected. Cannot compute shortest paths." << std::endl;
    }

    return 0;
}
