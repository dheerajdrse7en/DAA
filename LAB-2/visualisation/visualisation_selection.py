import pandas as pd
import matplotlib.pyplot as plt
from tabulate import tabulate
import os

perf_file = os.path.join("..", "performance", "selection_sort.csv")
df = pd.read_csv(perf_file)

print("\n=== Selection Sort Performance ===")
print(tabulate(df, headers='keys', tablefmt='fancy_grid', showindex=False))

plt.figure(figsize=(8, 5))
for scenario in df['Scenario'].unique():
    subset = df[df['Scenario'] == scenario]
    plt.plot(subset['Input Size'], subset['Time Taken'], marker='o', label=scenario)

plt.title("Selection Sort Performance")
plt.xlabel("Input Size (records)")
plt.ylabel("Time Taken (seconds)")
plt.legend()
plt.grid(True)
plt.tight_layout()

os.makedirs("graphs", exist_ok=True)
graph_path = os.path.join("graphs", "selection_sort_performance.png")
plt.savefig(graph_path)
plt.show()

print(f"\nGraph saved at {graph_path}")
