#include "Graph.h"
#include <iostream>

Graph::Graph(int V) {
    this->V = V;
    residualGraph.assign(V, std::vector<int>(V, 0));
}

void Graph::addEdge(int u, int v, int capacity) {
    residualGraph[u][v] = capacity;
}

bool Graph::bfs(int s, int t, std::vector<int>& parent) {
    std::vector<bool> visited(V, false);
    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && residualGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[t];
}

int Graph::edmondsKarp(int source, int sink) {
    int maxFlow = 0;
    std::vector<int> parent(V, -1);

    while (bfs(source, sink, parent)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, residualGraph[u][v]);
        }
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

void Graph::initializePreflow(int source) {
    height.assign(V, 0); 
    excess.assign(V, 0); 
    height[source] = V; 

    for (int v = 0; v < V; ++v) {
        if (residualGraph[source][v] > 0) {
            int capacity = residualGraph[source][v];
            excess[v] = capacity; 
            excess[source] -= capacity; 
            residualGraph[source][v] = 0;
            residualGraph[v][source] = capacity;
        }
    }
}

void Graph::push(int u, int v) {
    int send = std::min(excess[u], residualGraph[u][v]);
    residualGraph[u][v] -= send;
    residualGraph[v][u] += send;
    excess[u] -= send;
    excess[v] += send;
}


void Graph::relabel(int u) {
    int min_height = INT_MAX;
    for (int v = 0; v < V; ++v) {
        if (residualGraph[u][v] > 0) {  
            min_height = std::min(min_height, height[v]);
            height[u] = min_height + 1;
        }
    }
    if (min_height < INT_MAX) {
        
    }
}



void Graph::discharge(int u) {
    while (excess[u] > 0) {
        for (int v = 0; v < V && excess[u] > 0; ++v) {
            if (residualGraph[u][v] > 0 && (height[u] == height[v] + 1)) {
                push(u, v);
            }
        }
        if (excess[u] > 0) {
            relabel(u);
        }
    }
}

void Graph::globalRelabel(int source, int sink) {
    height.assign(V, V);
    height[sink] = 0;

    std::queue<int> q;
    q.push(sink);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; ++v) {
            if (residualGraph[v][u] > 0 && height[v] == V) {
                height[v] = height[u] + 1;
                q.push(v);
            }
        }
    }
}


int Graph::getHighestExcessVertex() {
    int source = 0;
    int sink = V - 1;
    int highestExcessVertex = -1;
    for (int v = 0; v < V; ++v) {
        if (v != source && v != sink && excess[v] > 0 && (highestExcessVertex == -1 || height[v] > height[highestExcessVertex])) {
            highestExcessVertex = v;
        }
    }
    return highestExcessVertex;
}

int Graph::getMaxFlow(int source, int sink) {
    initializePreflow(source);
    int highestExcessVertex = getHighestExcessVertex();
    while (highestExcessVertex != -1) {
        int oldHeight = height[highestExcessVertex];
        discharge(highestExcessVertex);
        if (height[highestExcessVertex] > oldHeight) {
            globalRelabel(source, sink);
        }
        highestExcessVertex = getHighestExcessVertex();
    }
    return excess[sink];
}