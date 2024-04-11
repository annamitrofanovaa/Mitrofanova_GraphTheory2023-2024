#найти какой максимальный ранг 
from collections import defaultdict
from typing import List

class Solution:
    def maximalNetworkRank(self, n: int, roads: List[List[int]]) -> int:
        city_connections = defaultdict(int)

        for road in roads:
            city_connections[road[0]] += 1
            city_connections[road[1]] += 1

        max_rank = 0

        for i in range(n):
            for j in range(i + 1, n):
                #общий ранг
                total_rank = city_connections[i] + city_connections[j]
                if [i, j] in roads or [j, i] in roads:
                    total_rank -= 1

                max_rank = max(max_rank, total_rank)

        return max_rank

