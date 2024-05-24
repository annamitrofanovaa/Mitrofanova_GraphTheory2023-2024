import networkx as nx
import random
import os

def generate_random_graphs(n, m, U, num_graphs, output_folder):
    os.makedirs(output_folder, exist_ok=True)

    for i in range(num_graphs):
        graph = nx.gnm_random_graph(n, m, seed=i)
        
        capacities = {edge: random.randint(1, U) for edge in graph.edges}
        
        filename = os.path.join(output_folder, f"test{i+1}.txt")
        with open(filename, 'w') as file:
            file.write(f"{n} {m}\n")
            for u, v in graph.edges:
                file.write(f"{u+1} {v+1} {capacities[(u, v)]}\n")

if __name__ == "__main__":
    n = int(input("Enter number of vertices (n): "))
    m = int(input("Enter number of edges (m): "))
    U = int(input("Enter maximum capacity (U): "))
    num_graphs = 50
    output_folder = "graph_tests"

    generate_random_graphs(n, m, U, num_graphs, output_folder)
    print(f"{num_graphs} graph files have been generated in the '{output_folder}' folder.")
