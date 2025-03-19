class Graph:
    def __init__(self, size):
        """Initialize adjacency matrix and vertex data storage."""
        self.size = size
        self.adj_matrix = [[0] * size for _ in range(size)]
        self.vertex_data = [''] * size  

    def add_edge(self, u: int, v: int):
        """Adds a directed edge from u -> v."""
        if 0 <= u < self.size and 0 <= v < self.size:
            self.adj_matrix[u][v] = 1  # Directed edge from u to v

    def add_vertex_data(self, vertex: int, data: str):
        """Assigns data to a vertex."""
        if 0 <= vertex < self.size:
            self.vertex_data[vertex] = data

    def print_graph(self):
        """Prints the adjacency matrix and vertex data."""
        print("Adjacency Matrix:")
        for row in self.adj_matrix:
            print(" ".join(map(str, row)))

        print("\nVertex Data:")
        for vertex, data in enumerate(self.vertex_data):
            print(f"Vertex {vertex}: {data}")

    def dfs_cycle_detection(self, v: int, visited: list, recStack: list) -> bool:
        """Helper DFS function for detecting cycles."""
        visited[v] = True
        recStack[v] = True
        print(f"Visiting: {self.vertex_data[v]}")

        for neighbor in range(self.size):
            if self.adj_matrix[v][neighbor]:  # If edge exists v → neighbor
                if not visited[neighbor]:
                    if self.dfs_cycle_detection(neighbor, visited, recStack):
                        return True
                elif recStack[neighbor]:  # Back edge detected (cycle)
                    print(f"Cycle detected at {self.vertex_data[neighbor]}!")
                    return True

        recStack[v] = False  # Remove from recursion stack before backtracking
        return False

    def is_cyclic(self) -> bool:
        """Checks if the graph contains a cycle using DFS."""
        visited = [False] * self.size
        recStack = [False] * self.size  # Recursion stack to track back edges

        for node in range(self.size):
            if not visited[node]:  # Perform DFS for unvisited nodes
                print()  # Print a newline for better readability
                if self.dfs_cycle_detection(node, visited, recStack):
                    return True
        return False


# Example Usage
g = Graph(7)

# Adding vertex data (optional)
g.add_vertex_data(0, 'A')
g.add_vertex_data(1, 'B')
g.add_vertex_data(2, 'C')
g.add_vertex_data(3, 'D')
g.add_vertex_data(4, 'E')
g.add_vertex_data(5, 'F')
g.add_vertex_data(6, 'G')

# Adding directed edges
g.add_edge(3, 0)  # D → A
g.add_edge(0, 2)  # A → C
g.add_edge(2, 1)  # C → B
g.add_edge(2, 4)  # C → E
g.add_edge(1, 5)  # B → F
g.add_edge(4, 0)  # E → A  (Cycle exists: A → C → E → A)
g.add_edge(2, 6)  # C → G

# Print graph structure
g.print_graph()

# Detect cycle
print("\nGraph has cycle:", g.is_cyclic())
