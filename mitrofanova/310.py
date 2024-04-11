#Среди всех возможных деревьев найти деревья минимальной высоты (MHT)

from collections import defaultdict, deque
from typing import List

class Solution:
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:
        if n == 1:
            return [0]

        graph = defaultdict(list)
        for edge in edges:
            graph[edge[0]].append(edge[1])
            graph[edge[1]].append(edge[0])

        #листья добавляем в очередь
        leaves = deque(node for node in graph if len(graph[node]) == 1)

        while n > 2:
            #убираем листья
            current_leaves = len(leaves)
            n -= current_leaves
            for _ in range(current_leaves):
                leaf = leaves.popleft()
                neighbor = graph[leaf].pop()
                graph[neighbor].remove(leaf)
                if len(graph[neighbor]) == 1:
                    leaves.append(neighbor)

        return list(leaves)
    