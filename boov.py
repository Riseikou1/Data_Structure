from collections import deque

class Graph :
    def __init__(self,size):
        self.size = size
        self.adj_matrix = [[0]*size for _ in range(size)]
        self.vertex_data = ['']*size

    def add_edge(self,u,v,capacity):
        self.adj_matrix[u][v] = capacity

    def add_vertex_data(self,vertex,data):
        if 0<=vertex<self.size :
            self.vertex_data[vertex] = data

    def bfs(self,source,sink,parent):
        visited = [False]*self.size
        queue = deque([source])
        visited[source] = True
        parent[source] = -1

        while queue :
            u = queue.popleft()
            for v,capacity in enumerate(self.adj_matrix[u]) :
                if not visited[v] and capacity > 0 :
                    parent[v] = u
                    visited[v] = True
                    queue.append(v)
                    if v == sink :
                        return True
        return False
    
    def edmonds_karp(self,source,sink):
        parent = [-1]*self.size
        max_flow = 0

        print("*"*45)
        print("Augmenting Paths Found: ")

        while self.bfs(source,sink,parent):
            path_flow = float("inf")
            v = sink

            while v != source :
                u = parent[v]
                path_flow = min(path_flow,self.adj_matrix[u][v])
                v = u

            v = sink
            while v != source :
                u = parent[v]
                self.adj_matrix[u][v] -= path_flow
                self.adj_matrix[v][u] += path_flow
                v = u

            max_flow += path_flow

            path = []
            v = sink
            while v != -1 :
                path.append(self.vertex_data[v])
                v = parent[v]
            path.reverse()
            print("Path :"," -> ".join(path), f" || Flow : {path_flow}")

        print("*"*45)
        return max_flow
    
g = Graph(6)
vertex_names = ['s', 'v1', 'v2', 'v3', 'v4', 't']
for i, name in enumerate(vertex_names):
    g.add_vertex_data(i, name)

g.add_edge(0, 1, 3)  # s -> v1
g.add_edge(0, 2, 7)  # s -> v2
g.add_edge(1, 3, 3)  # v1 -> v3
g.add_edge(1, 4, 4)  # v1 -> v4
g.add_edge(2, 1, 5)  # v2 -> v1
g.add_edge(2, 4, 3)  # v2 -> v4
g.add_edge(3, 4, 3)  # v3 -> v4
g.add_edge(3, 5, 2)  # v3 -> t
g.add_edge(4, 5, 6)  # v4 -> t

source = 0  # s
sink = 5    # t
print(f"The maximum possible flow is: {g.edmonds_karp(source, sink)}")
print("*"*45)
