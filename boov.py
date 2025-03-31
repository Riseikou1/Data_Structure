class Graph:
    def __init__(self, size):
        self.adj_matrix = [[0] * size for _ in range(size)]  # Initialize adjacency matrix
        self.size = size
        self.vertex_data = [''] * size  # Vertex labels

    def add_edge(self, u, v, weight):
        if 0 <= u < self.size and 0 <= v < self.size:
            self.adj_matrix[u][v] = weight  # Also for the Directed edge (no need for the reverse edge)

    def add_vertex_data(self, vertex, data):
        if 0 <= vertex < self.size:
            self.vertex_data[vertex] = data

    def bellman_ford(self, start_vertex_data):
        start_vertex = self.vertex_data.index(start_vertex_data)  # Start vertex index
        distances = [float('inf')] * self.size  # Initialize distances as infinity
        predecessors = [None] * self.size  # Predecessors to track paths
        distances[start_vertex] = 0  # Distance to start vertex is 0

        # Relax edges |V| - 1 times
        for _ in range(self.size - 1):
            updated = False
            for u in range(self.size):
                for v in range(self.size):
                    if self.adj_matrix[u][v] != 0:  # If there's an edge from u to v
                        new_dist = distances[u] + self.adj_matrix[u][v]
                        if new_dist < distances[v]:  # Relax the edge
                            distances[v] = new_dist
                            predecessors[v] = u
                            updated = True
            if not updated :
                break  # can stop the iteration if nothing has improved during a full pass.
        # Negative cycle detection (after all relaxations)
        for u in range(self.size):
            for v in range(self.size):
                if self.adj_matrix[u][v] != 0 and distances[u] + self.adj_matrix[u][v] < distances[v]:
                    return True, None, None  # Negative cycle detected

        return False, distances, predecessors

    def get_path(self, predecessors, start_vertex_data, end_vertex_data):
        start_vertex = self.vertex_data.index(start_vertex_data)
        end_vertex = self.vertex_data.index(end_vertex_data)

        path = []
        current = end_vertex
        while current is not None:
            path.insert(0, self.vertex_data[current])  # Insert at the beginning of the list
            current = predecessors[current]
            if current == start_vertex:  # Stop when we reach the start vertex
                path.insert(0, self.vertex_data[start_vertex])
                break
        return '->'.join(path)  # Return the path as a string

# Example Usage
g = Graph(5)

# Add vertices with labels
g.add_vertex_data(0, 'A')
g.add_vertex_data(1, 'B')
g.add_vertex_data(2, 'C')
g.add_vertex_data(3, 'D')
g.add_vertex_data(4, 'E')

# Add directed edges with weights
g.add_edge(3, 0, 4)  # D -> A, weight 4
g.add_edge(3, 2, 7)  # D -> C, weight 7
g.add_edge(3, 4, 3)  # D -> E, weight 3
g.add_edge(0, 2, 4)  # A -> C, weight 4
g.add_edge(2, 0, -3) # C -> A, weight -3
g.add_edge(0, 4, 5)  # A -> E, weight 5
g.add_edge(4, 2, 3)  # E -> C, weight 3
g.add_edge(1, 2, -4) # B -> C, weight -4
g.add_edge(4, 1, 2)  # E -> B, weight 2

# Running the Bellman-Ford algorithm from D to all vertices
print("\nThe Bellman-Ford Algorithm starting from vertex D:")
negative_cycle, distances, predecessors = g.bellman_ford('D')

if not negative_cycle:
    for i, d in enumerate(distances):
        if d != float('inf'):
            path = g.get_path(predecessors, 'D', g.vertex_data[i])
            print(f"Shortest path from D to {g.vertex_data[i]}: {path}, Distance: {d}")
        else:
            print(f"No path from D to {g.vertex_data[i]}, Distance: Infinity")
else:
    print("Negative weight cycle detected. Cannot compute shortest paths.")
