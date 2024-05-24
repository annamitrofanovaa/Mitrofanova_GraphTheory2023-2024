#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>


class Graph {
    int V;
   // int flow;

   // std::vector<std::vector<int>> residualGraph;
    std::vector<std::vector<int>> residualGraph; // Остаточная ёмкость графа
    std::vector<int> excess; // Высота и избыточный поток вершин
    std::vector<int> height;

public:
    void initializePreflow(int source);
    void push(int u, int v);
    void relabel(int u);
    void discharge(int u);
    void globalRelabel(int source, int sink);
    int getMaxFlow(int source, int sink);
    int getHighestExcessVertex();
    // Конструктор
    Graph(int V);

    // Деструктор
    ~Graph() = default;

    void addEdge(int u, int v, int capacity);
    bool bfs(int s, int t, std::vector<int>& parent);
    int edmondsKarp(int source, int sink);
   
};


#endif
