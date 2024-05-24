import matplotlib.pyplot as plt

file_path = 'results.txt'
with open(file_path, 'r') as file:
    lines = file.readlines()

num_vertices = int(lines[0].strip())
num_edges = int(lines[1].strip())
edmonds_karp_times = [int(lines[i].strip()) for i in range(2, 52)]
push_relabel_times = [int(lines[i].strip()) for i in range(52, 102)]

avg_edmonds_karp_time = sum(edmonds_karp_times) / len(edmonds_karp_times)
avg_push_relabel_time = sum(push_relabel_times) / len(push_relabel_times)

plt.figure(figsize=(12, 6))
plt.plot(edmonds_karp_times, label='Edmonds-Karp')
plt.plot(push_relabel_times, label='Push-Relabel')
plt.axhline(y=avg_edmonds_karp_time, color='b', linestyle='--', label=f'Avg Edmonds-Karp Time: {avg_edmonds_karp_time:.2f} ms')
plt.axhline(y=avg_push_relabel_time, color='r', linestyle='--', label=f'Avg Push-Relabel Time: {avg_push_relabel_time:.2f} ms')
plt.xlabel('Test Run')
plt.ylabel('Time (ms)')
plt.title(f'Performance Comparison\nVertices: {num_vertices}, Edges: {num_edges}')
plt.legend()
plt.grid(True)
plt.savefig('performance_comparison_with_avg.png')
plt.show()

print(f'Average Edmonds-Karp Time: {avg_edmonds_karp_time:.2f} ms')
print(f'Average Push-Relabel Time: {avg_push_relabel_time:.2f} ms')
