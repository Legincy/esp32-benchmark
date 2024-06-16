import json
import matplotlib.pyplot as plt
import numpy as np

with open('result.json', 'r') as f:
    data = json.load(f)

data_c = next(item['data'] for item in data if item['type'] == 'c')
data_python = next(item['data'] for item in data if item['type'] == 'python')

names_c = [entry['name'] for entry in data_c]
durations_c = [entry['duration'] for entry in data_c]

names_python = [entry['name'] for entry in data_python]
durations_python = [entry['duration'] for entry in data_python]

bar_width = 0.35
index = np.arange(len(names_c))

fig, ax = plt.subplots(figsize=(12, 8))

bar1 = ax.bar(index, durations_c, bar_width, label='C', color='b', alpha=0.6)
bar2 = ax.bar(index + bar_width, durations_python, bar_width, label='Python', color='r', alpha=0.6)

ax.set_xlabel('Operationen')
ax.set_ylabel('Dauer in Mikrosekunden (log skaliert)')
ax.set_title('Vergleich der Operationen zwischen C und Python auf einem ESP32')
ax.set_xticks(index + bar_width / 2)
ax.set_xticklabels(names_c, rotation=90)
ax.legend()

ax.set_yscale('log')

plt.tight_layout()
plt.savefig('plot.png')
plt.show()
