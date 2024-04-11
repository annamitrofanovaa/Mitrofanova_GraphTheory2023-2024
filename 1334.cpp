#include <vector>
#include <algorithm>
#include <unordered_map>

class Solution {
public:
    int findTheCity(int n, std::vector<std::vector<int>>& edges, int distanceThreshold) {
        std::vector<std::vector<int>> dist(n, std::vector<int>(n, INT_MAX));
        for (int i = 0; i < n; ++i)
            dist[i][i] = 0; 

        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            dist[u][v] = dist[v][u] = w;
        }

        //алгоритм Флойда-Уоршелла для поиска кратчайших путей между всеми парами городов
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        std::unordered_map<int, int> reachable_cities;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] <= distanceThreshold)
                    reachable_cities[i]++;
            }
        }

        int min_reachable = INT_MAX;
        for (const auto& entry : reachable_cities) {
            min_reachable = std::min(min_reachable, entry.second);
        }

        std::vector<int> min_reachable_cities;
        for (const auto& entry : reachable_cities) {
            if (entry.second == min_reachable)
                min_reachable_cities.push_back(entry.first);
        }
        
        return *std::max_element(min_reachable_cities.begin(), min_reachable_cities.end());
    }
};
