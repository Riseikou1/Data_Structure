#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

class Graph {
private:
    int size;
    vector<vector<int>> adj_matrix;
    vector<string> vertex_data;

public:
    Graph(int n) : size(n), adj_matrix(n, vector<int>(n, 0)), vertex_data(n, "") {}

    void add_vertex_data(int vertex, const string& data) {
        if (vertex >= 0 && vertex < size)
            vertex_data[vertex] = data;
    }

    void add_edge(int u, int v, int weight, bool bidirectional = false) {
        if (u >= 0 && u < size && v >= 0 && v < size) {
            adj_matrix[u][v] = weight;
            if (bidirectional)
                adj_matrix[v][u] = weight;
        }
    }

    void dijkstra(const string& start_vertex_data, vector<int>& distances, vector<int>& previous) {
        int start = find(vertex_data.begin(), vertex_data.end(), start_vertex_data) - vertex_data.begin();

        distances.assign(size, numeric_limits<int>::max());
        previous.assign(size, -1);
        vector<bool> visited(size, false);
        distances[start] = 0;

        // Min-heap using pair: (distance, vertex)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> min_heap;
        min_heap.push({0, start});

        while (!min_heap.empty()) {
            auto [current_dist, u] = min_heap.top();
            min_heap.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (int v = 0; v < size; ++v) {
                int weight = adj_matrix[u][v];
                if (weight != 0 && !visited[v]) {
                    int new_dist = current_dist + weight;
                    if (new_dist < distances[v]) {
                        distances[v] = new_dist;
                        previous[v] = u;
                        min_heap.push({new_dist, v});
                    }
                }
            }
        }
    }

    void print_paths(const string& start_vertex_data, const vector<int>& distances, const vector<int>& previous) {

        cout << "\nShortest paths from " << start_vertex_data << ":\n";
        cout << "----------------------------------------\n";

        for (int i = 0; i < size; ++i) {
            vector<string> path;
            int j = i;
            while (j != -1) {
                path.push_back(vertex_data[j]);
                j = previous[j];
            }
            reverse(path.begin(), path.end());

            cout << start_vertex_data << " to " << vertex_data[i] << ": ";
            for (size_t k = 0; k < path.size(); ++k) {
                cout << path[k];
                if (k != path.size() - 1)
                    cout << " -> ";
            }

            if (distances[i] == numeric_limits<int>::max())
                cout << " | Distance: ∞" << endl;
            else
                cout << " | Distance: " << distances[i] << endl;
        }
    }
};

// === Main Function ===

int main() {
    Graph g(7);
    vector<string> labels = {"A", "B", "C", "D", "E", "F", "G"};
    for (int i = 0; i < labels.size(); ++i)
        g.add_vertex_data(i, labels[i]);

    g.add_edge(3, 0, 4); // D -> A
    g.add_edge(3, 4, 2); // D -> E
    g.add_edge(0, 2, 3); // A -> C
    g.add_edge(0, 4, 4); // A -> E
    g.add_edge(4, 2, 4); // E -> C
    g.add_edge(4, 6, 5); // E -> G
    g.add_edge(2, 5, 5); // C -> F
    g.add_edge(2, 1, 2); // C -> B
    g.add_edge(1, 5, 2); // B -> F
    g.add_edge(6, 5, 5); // G -> F

    vector<int> distances, previous;
    g.dijkstra("D", distances, previous);
    g.print_paths("D", distances, previous);

    return 0;
}
