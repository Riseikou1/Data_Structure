class Graph:
    def __init__(self, size):
        self.size = size
        self.edges = []  # List of (u, v, weight)
        self.vertex_data = [''] * size  # Human-readable vertex labels

    def add_edge(self, u, v, weight):
        if 0 <= u < self.size and 0 <= v < self.size:
            self.edges.append((u, v, weight))

    def add_vertex_data(self, vertex, data):
        if 0 <= vertex < self.size:
            self.vertex_data[vertex] = data

    def find(self, parent, i):
        # Path compression
        if parent[i] != i:
            parent[i] = self.find(parent, parent[i])
        return parent[i]

    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def kruskals_algorithm(self):
        result = []  # Store MST edges

        # Step 1: Sort edges by weight
        self.edges.sort(key=lambda edge: edge[2])

        # Step 2: Create disjoint sets
        parent = list(range(self.size))
        rank = [0] * self.size

        for u, v, weight in self.edges:
            root_u = self.find(parent, u)
            root_v = self.find(parent, v)

            if root_u != root_v:
                result.append((u, v, weight))
                self.union(parent, rank, root_u, root_v)

        # Print MST
        print("Edge \tWeight")
        for u, v, weight in result:
            print(f"{self.vertex_data[u]}-{self.vertex_data[v]} \t{weight}")

g = Graph(7)
labels = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
for i, label in enumerate(labels):
    g.add_vertex_data(i, label)

g.add_edge(0, 1, 4)   # A-B
g.add_edge(0, 6, 10)  # A-G
g.add_edge(0, 2, 9)   # A-C
g.add_edge(1, 2, 8)   # B-C
g.add_edge(2, 3, 5)   # C-D
g.add_edge(2, 4, 2)   # C-E
g.add_edge(2, 6, 7)   # C-G
g.add_edge(3, 4, 3)   # D-E
g.add_edge(3, 5, 7)   # D-F
g.add_edge(4, 6, 6)   # E-G
g.add_edge(5, 6, 11)  # F-G

print("Kruskal's Algorithm MST:")
g.kruskals_algorithm()
