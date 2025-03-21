import heapq

class Graph:
    def __init__(self, size):
        self.size = size
        self.adj_matrix = [[0] * size for _ in range(size)]  # Adjacency matrix
        self.vertex_data = [''] * size  # Labels for vertices

    def add_edge(self, u, v, weight, bidirectional=False):
        if 0 <= u < self.size and 0 <= v < self.size:
            self.adj_matrix[u][v] = weight
            if bidirectional:
                self.adj_matrix[v][u] = weight  # Undirected graph: add reverse edge

    def add_vertex_data(self, vertex, data):
        if 0 <= vertex < self.size:
            self.vertex_data[vertex] = data

    def dijkstra(self, start_vertex_data, end_vertex_data):
        start_vertex = self.vertex_data.index(start_vertex_data)
        end_vertex = self.vertex_data.index(end_vertex_data)

        distances = [float('inf')] * self.size  # Distances from start to all vertices
        predecessors = [None] * self.size  # Tracks the predecessors of each vertex
        distances[start_vertex] = 0  # Start vertex has distance 0

        # Min-heap to always fetch the vertex with the smallest distance
        min_heap = [(0, start_vertex)]  # Initial heap with start vertex distance

        while min_heap:
            current_dist, u = heapq.heappop(min_heap)

            # Skip if the popped node is already not optimal
            if current_dist > distances[u]:
                continue

            # Update the distances to neighbors
            for v in range(self.size):
                weight = self.adj_matrix[u][v]
                if weight != 0:  # Only consider valid, non-zero weight neighbors
                    alt = current_dist + weight
                    if alt < distances[v]:  # Found a shorter path to v
                        distances[v] = alt
                        predecessors[v] = u  # Update the predecessor of v
                        heapq.heappush(min_heap, (alt, v))  # Push new path into the heap

            # If we have reached the end vertex, break early
            if u == end_vertex:
                break

        # Return the distance to the end vertex and the shortest path
        if distances[end_vertex] == float('inf'):
            return float('inf'), []  # No path exists
        return distances[end_vertex], self.construct_path(predecessors, start_vertex, end_vertex)

    def construct_path(self, predecessors, start_vertex, end_vertex):
        # Backtrack to reconstruct the shortest path from end to start
        path = []
        current = end_vertex
        while current is not None:
            path.insert(0, self.vertex_data[current])
            current = predecessors[current]

        # If the start and end vertices are the same
        if path[0] == self.vertex_data[start_vertex]:
            return path
        else:
            return []  # No path found (disconnected graph)

    def print_path_and_distance(self, start_vertex_data, end_vertex_data):
        distance, path = self.dijkstra(start_vertex_data, end_vertex_data)

        if distance == float('inf'):
            print(f"No path from {start_vertex_data} to {end_vertex_data}")
        else:
            path_str = " -> ".join(path)
            print(f"Shortest Path from {start_vertex_data} to {end_vertex_data}: {path_str}, Distance: {distance}")

# Example Usage

g = Graph(7)

# Add vertex labels
labels = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
for i, label in enumerate(labels):
    g.add_vertex_data(i, label)

# Add directed edges
g.add_edge(3, 0, 4)  # D -> A
g.add_edge(3, 4, 2)  # D -> E
g.add_edge(0, 2, 3)  # A -> C
g.add_edge(0, 4, 4)  # A -> E
g.add_edge(4, 2, 4)  # E -> C
g.add_edge(4, 6, 5)  # E -> G
g.add_edge(2, 5, 5)  # C -> F
g.add_edge(2, 1, 2)  # C -> B
g.add_edge(1, 5, 2)  # B -> F
g.add_edge(6, 5, 5)  # G -> F

# Print shortest path and distance from 'D' to 'F'
g.print_path_and_distance('D', 'F')
