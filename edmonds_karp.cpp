#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>

using namespace std;

struct Edge {
    int to, rev;
    int capacity;
};

class MaxFlow {
    int size;
    vector<vector<Edge>> graph;

public:
    MaxFlow(int n) : size(n), graph(n) {}

    void add_edge(int from, int to, int cap) {
        graph[from].push_back({to, (int)graph[to].size(), cap});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0}); // reverse edge
    }

    int edmonds_karp(int s, int t) {
        int max_flow = 0;

        while (true) {
            vector<int> parent(size, -1);
            vector<int> edge_index(size, -1);
            queue<int> q;
            q.push(s);
            parent[s] = s;

            while (!q.empty() && parent[t] == -1) {
                int u = q.front(); q.pop();
                for (int i = 0; i < graph[u].size(); ++i) {
                    const Edge& e = graph[u][i];
                    if (parent[e.to] == -1 && e.capacity > 0) {
                        parent[e.to] = u;
                        edge_index[e.to] = i;
                        q.push(e.to);
                        if (e.to == t) break;
                    }
                }
            }

            if (parent[t] == -1) break; // No augmenting path found

            // Find bottleneck
            int path_flow = INT_MAX;
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                const Edge& e = graph[u][edge_index[v]];
                path_flow = min(path_flow, e.capacity);
            }

            // Update residual graph
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                Edge& e = graph[u][edge_index[v]];
                e.capacity -= path_flow;
                graph[e.to][e.rev].capacity += path_flow;
            }

            max_flow += path_flow;
        }

        return max_flow;
    }
};
