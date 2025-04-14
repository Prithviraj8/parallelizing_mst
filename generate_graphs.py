import matplotlib.pyplot as plt
import numpy as np

# Data for Prim's Algorithm
prims_data = {
    'small': {  # 100V, 4000E
        'bubble': [1.78, 2.22, 2.42, 3.96],
        'quick': [2.53, 2.16, 1.82, 2.52],
        'merge': [1.55, 1.71, 2.54, 3.98]
    },
    'medium': {  # 1000V, 20000E
        'bubble': [19.09, 13.09, 10.31, 14.11],
        'quick': [20.11, 20.08, 14.81, 439.59],
        'merge': [20.50, 14.39, 11.72, 14.78]
    },
    'large': {  # 1500V, 50000E
        'bubble': [41.94, 25.49, 17.25, 20.04],
        'quick': [40.12, 26.02, 19.87, 26.76],
        'merge': [41.02, 27.63, 19.53, 22.70]
    }
}

# Data for Kruskal's Algorithm
kruskals_data = {
    'small': {  # 100V, 4000E
        'bubble': [5.86, 7.18, 6.56, 8.07],
        'quick': [254.57, 118.01, 71.09, 65.10],
        'merge': [2.62, 1.69, 1.41, 1.54]
    },
    'medium': {  # 1000V, 20000E
        'bubble': [30.99, 31.08, 32.01, 34.55],
        'quick': [6235.17, 3068.81, 2139.03, 1643.91],
        'merge': [14.49, 8.07, 5.15, 4.13]
    },
    'large': {  # 1500V, 50000E
        'bubble': [88.16, 84.08, 82.59, 92.64],
        'quick': [36348.45, 18071.52, 11513.93, 9498.78],
        'merge': [35.00, 19.66, 13.83, 11.75]
    }
}

def create_performance_graph(data, title, filename):
    threads = [1, 2, 4, 8]
    plt.figure(figsize=(12, 6))
    
    for size in ['small', 'medium', 'large']:
        for sort in ['bubble', 'quick', 'merge']:
            label = f"{size.capitalize()} Graph - {sort.capitalize()} Sort"
            plt.plot(threads, data[size][sort], marker='o', label=label)
    
    plt.xlabel('Number of Threads')
    plt.ylabel('Time (ms)')
    plt.title(title)
    plt.grid(True)
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.tight_layout()
    plt.savefig(filename)
    plt.close()

# Create graphs
create_performance_graph(prims_data, "Prim's Algorithm Performance", 'prims_comparison.png')
create_performance_graph(kruskals_data, "Kruskal's Algorithm Performance", 'kruskals_comparison.png')

# Create separate graphs for each graph size
sizes = ['small', 'medium', 'large']
size_labels = {
    'small': '100V, 4000E',
    'medium': '1000V, 20000E',
    'large': '1500V, 50000E'
}

for size in sizes:
    plt.figure(figsize=(12, 6))
    threads = [1, 2, 4, 8]
    
    # Prim's data
    for sort in ['bubble', 'quick', 'merge']:
        label = f"Prim's - {sort.capitalize()} Sort"
        plt.plot(threads, prims_data[size][sort], marker='o', linestyle='-', label=label)
    
    # Kruskal's data
    for sort in ['bubble', 'quick', 'merge']:
        label = f"Kruskal's - {sort.capitalize()} Sort"
        plt.plot(threads, kruskals_data[size][sort], marker='s', linestyle='--', label=label)
    
    plt.xlabel('Number of Threads')
    plt.ylabel('Time (ms)')
    plt.title(f'Performance Comparison - {size_labels[size]}')
    plt.grid(True)
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.tight_layout()
    plt.savefig(f'{size}_comparison.png')
    plt.close() 