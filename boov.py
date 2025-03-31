class Graph :
    def __init__(self,size):
        self.size = size
        self.adj_matrix = [[0]*size for _ in range(size)]
        self.vertex_data = ['']*size
    
    def add_vertex_data(self,vertex,data):
        if 0<= vertex < self.size:
            self.vertex_data[vertex] = data

    def add_edge(self,u,v,weight):
        if 0<=u<self.size and 0<=v<self.size :
            self.adj_matrix[u][v] = weight
            self.adj_matrix[v][u] = weight # For undirected Graph.
        
    def prims_algorithm(self):
        key = [float("inf")] * self.size
        parent = [-1]*self.size
        in_mst = [False]* self.size

        key[0] =0

        for _ in range(self.size):
            # Find the vertex with the minimum key value not in MST
            u = min((v for v in range(self.size) if not in_mst[v]),key=lambda x: key[x])
            in_mst[u] = True

            # Update the key and parent of adjacent vertices
            for v in range(self.size):
                weight = self.adj_matrix[u][v]
                if weight > 0 and not in_mst[v] and weight < key[v]:
                    key[v] = weight
                    parent[v] = u
        
        print("*"*40 + "\nPrim's Algorithm - Minimum Spanning Tree:\n"+"*"*40)
        print("Edge\tWeight")
        total_weight = 0
        for v in range(1,self.size):
            u = parent[v]
            weight = self.adj_matrix[u][v]
            print(f"{self.vertex_data[u]} - {self.vertex_data[v]}\t{weight}")
            total_weight += weight
        print(f"Total Weight of MST : {total_weight}")

g = Graph(8)

# Assign labels to vertices
labels = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']

for i,data in enumerate(labels):
    g.add_vertex_data(i,data)

# Add undirected edges with weights
edges = [
    (0, 1, 4), (0, 3, 3), (1, 2, 3), (1, 3, 5), (1, 4, 6),
    (2, 4, 4), (2, 7, 2), (3, 4, 7), (3, 5, 4),
    (4, 5, 5), (4, 6, 3), (5, 6, 7), (6, 7, 5)
]

for u,v,w in edges :
    g.add_edge(u,v,w)

g.prims_algorithm()
