import heapq
from typing import List

class Solution:
    def countPaths(self, n: int, roads: List[List[int]]) -> int:
        MOD = 10**9 + 7
        graph = {i: [] for i in range(n)}
        times = {i: float('inf') for i in range(n)}
        times[0] = 0

        for road in roads:
            graph[road[0]].append((road[1], road[2]))
            graph[road[1]].append((road[0], road[2]))

        min_heap = [(0, 0)]  #время, пересечение
        while min_heap:
            current_time, current_intersection = heapq.heappop(min_heap)
            if current_time > times[current_intersection]:
                continue

            for neighbor, time_to_neighbor in graph[current_intersection]:
                total_time = current_time + time_to_neighbor
                if total_time < times[neighbor]:
                    times[neighbor] = total_time
                    heapq.heappush(min_heap, (total_time, neighbor))

        count = [0] * n
        count[0] = 1  #источник
        for i in range(1, n):
            for neighbor, time_to_neighbor in graph[i]:
                if times[neighbor] + time_to_neighbor == times[i]:
                    count[i] = (count[i] + count[neighbor]) % MOD

        return count[n - 1]