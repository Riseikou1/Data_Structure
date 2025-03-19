class Graph:
    def __init__(self, size):
        self.size = size
        self.adj_list = [[] for _ in range(size)]  # Use adjacency list instead of matrix
        self.parent = list(range(size))  # Union-Find parent array
        self.rank = [0] * size  # Rank array for union by rank

    def add_edge(self, u, v):
        if 0 <= u < self.size and 0 <= v < self.size:
            self.adj_list[u].append(v)
            self.adj_list[v].append(u)

    def find(self, i):
        """Find root of i with path compression."""
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])  # Path compression
        return self.parent[i]

    def union(self, x, y):
        """Union by rank: attach smaller tree under larger tree."""
        root_x = self.find(x)
        root_y = self.find(y)

        if root_x != root_y:
            if self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
            elif self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
            else:
                self.parent[root_y] = root_x
                self.rank[root_x] += 1  # Increase rank of new root

    def is_cyclic(self):
        """Detect cycle using Union-Find (Disjoint Set)."""
        for u in range(self.size):
            for v in self.adj_list[u]:
                if u < v:  # To avoid duplicate checks
                    root_u = self.find(u)
                    root_v = self.find(v)
                    if root_u == root_v:
                        return True  # Cycle detected
                    self.union(root_u, root_v)
        return False


# Example Usage
g = Graph(7)

edges = [(1, 0), (0, 3), (0, 2), (2, 3), (3, 4), (3, 5), (3, 6), (4, 5)]
for u, v in edges:
    g.add_edge(u, v)

print("Graph has cycle:", g.is_cyclic())
