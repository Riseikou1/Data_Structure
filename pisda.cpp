#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Graph {
    int size;
    vector<vector<int>> adj_matrix;
    vector<string> vertex_data;

public:
    Graph(int size) : size(size), adj_matrix(size, vector<int>(size, 0)), vertex_data(size, "") {}

    // Add an edge with a given capacity
    void add_edge(int u, int v, int capacity) {
        adj_matrix[u][v] = capacity;
    }

    // Add vertex names
    void add_vertex_data(int vertex, const string& data) {
        if (vertex >= 0 && vertex < size) {
            vertex_data[vertex] = data;
        }
    }

    // DFS to find an augmenting path
    bool dfs(int s, int t, vector<bool>& visited, vector<int>& path) {
        visited[s] = true;
        path.push_back(s);

        if (s == t) {  // If we reached the sink, return the path
            return true;
        }

        for (int ind = 0; ind < size; ++ind) {
            if (!visited[ind] && adj_matrix[s][ind] > 0) {
                if (dfs(ind, t, visited, path)) {
                    return true;
                }
            }
        }

        path.pop_back();  // No path found, backtrack
        return false;
    }

    // Ford-Fulkerson algorithm to find the maximum flow
    int fordFulkerson(int source, int sink) {
        int max_flow = 0;
        
        while (true) {
            vector<int> path;
            vector<bool> visited(size, false);
            path.clear();
            
            if (!dfs(source, sink, visited, path)) {
                break;  // No augmenting path found
            }

            // Find the maximum flow in the current path
            int path_flow = INT_MAX;
            for (int i = 0; i < path.size() - 1; ++i) {
                int u = path[i];
                int v = path[i + 1];
                path_flow = min(path_flow, adj_matrix[u][v]);
            }

            // Update the residual graph
            for (int i = 0; i < path.size() - 1; ++i) {
                int u = path[i];
                int v = path[i + 1];
                adj_matrix[u][v] -= path_flow;
                adj_matrix[v][u] += path_flow;
            }

            max_flow += path_flow;

            // Print the path and the flow
            vector<string> path_names;
            for (int node : path) {
                path_names.push_back(vertex_data[node]);
            }
            cout << "Path: ";
            for (size_t i = 0; i < path_names.size(); ++i) {
                cout << path_names[i];
                if (i != path_names.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << " , Flow: " << path_flow << endl;
        }

        return max_flow;
    }
};

int main() {
    Graph g(6);
    vector<string> vertex_names = {"s", "v1", "v2", "v3", "v4", "t"};
    
    for (int i = 0; i < 6; ++i) {
        g.add_vertex_data(i, vertex_names[i]);
    }

    // Add edges with capacities
    g.add_edge(0, 1, 3);  // s  -> v1, cap: 3
    g.add_edge(0, 2, 7);  // s  -> v2, cap: 7
    g.add_edge(1, 3, 3);  // v1 -> v3, cap: 3
    g.add_edge(1, 4, 4);  // v1 -> v4, cap: 4
    g.add_edge(2, 1, 5);  // v2 -> v1, cap: 5
    g.add_edge(2, 4, 3);  // v2 -> v4, cap: 3
    g.add_edge(3, 4, 3);  // v3 -> v4, cap: 3
    g.add_edge(3, 5, 2);  // v3 -> t,  cap: 2
    g.add_edge(4, 5, 6);  // v4 -> t,  cap: 6

    // Source and Sink
    int source = 0, sink = 5;

    // Calculate and output the maximum flow
    int temuujin = g.fordFulkerson(source, sink);
    cout << "The maximum possible flow is : " << temuujin << endl; 

    return 0;
}
