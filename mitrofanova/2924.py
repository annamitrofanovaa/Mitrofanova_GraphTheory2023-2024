#найти победителя
from collections import defaultdict
from typing import List

class Solution:
    def findChampion(self, n: int, edges: List[List[int]]) -> int:
        incoming_edges = defaultdict(int)
        for edge in edges:
            incoming_edges[edge[1]] +=1
        
        result = -1
        for i in range(n):
            if i not in incoming_edges:
                if result == -1:
                    result = i
                else:
                    return -1
                    
        return result


