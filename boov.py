import heapq

class Graph:
    def __init__(self, size):
        self.size = size
        self.adj_matrix = [[0]*size for _ in range(size)]
        self.vertex_data = ['']*size

    def add_edge(self, u, v, weight, bidirectional=False):
        if 0 <= u < self.size and 0 <= v < self.size:
            self.adj_matrix[u][v] = weight
            if bidirectional:
                self.adj_matrix[v][u] = weight  # for undirected graph

    def add_vertex_data(self, vertex, data):
        if 0 <= vertex < self.size:
            self.vertex_data[vertex] = data

    def dijkstra(self, start_vertex_data):
        start = self.vertex_data.index(start_vertex_data)
        distances = [float('inf')] * self.size
        distances[start] = 0
        previous = [None] * self.size
        visited = [False] * self.size

        # Min-heap: (distance, vertex)
        min_heap = [(0, start)]

        while min_heap:
            current_dist, u = heapq.heappop(min_heap)

            if visited[u]:
                continue
            visited[u] = True

            for v in range(self.size):
                weight = self.adj_matrix[u][v]
                if weight != 0 and not visited[v]:
                    new_dist = current_dist + weight
                    if new_dist < distances[v]:
                        distances[v] = new_dist
                        previous[v] = u
                        heapq.heappush(min_heap, (new_dist, v))

        return distances, previous

    def print_paths(self, start_vertex_data, distances, previous):
        print(f"\nShortest paths from {start_vertex_data}:\n" + "-"*40)
        for i in range(self.size):
            path = []
            j = i
            while j is not None:
                path.insert(0, self.vertex_data[j])
                j = previous[j]
            path_str = " -> ".join(path)
            dist_str = f"∞" if distances[i] == float('inf') else distances[i]
            print(f"{start_vertex_data} to {self.vertex_data[i]}: {path_str} | Distance: {dist_str}")

# === Example Usage ===

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

# Run Dijkstra from vertex 'D'
distances, previous = g.dijkstra('D')
g.print_paths('D', distances, previous)
