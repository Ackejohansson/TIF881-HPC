import numpy as np
import matplotlib.pyplot as plt

values = np.array([205.9, 160.3, 138.3, 127.3, 116.3])
labels = ['Base\ncase', 'Algebraic\nexpression', 'Operand\ntype', 'Loop unroll\ncolumn', 'Loop unroll\nrow']
pm = np.array([11.8, 10.2, 10.1, 9.3, 5.2])

fig, ax = plt.subplots()
ax.errorbar(labels, values, yerr=pm, fmt='bo', label='Data', capsize=5)
ax.axhline(y=310, color='green', linestyle='--', label='Assignment timing goal')

plt.xticks(rotation=45, ha="right")
ax.set_ylabel('Execution Time (ms)')
ax.set_title('Execution Time for Different Optimizations')
ax.legend(loc='upper right')
ax.grid(True, linestyle='--', alpha=0.6)
fig.tight_layout()
plt.show()
