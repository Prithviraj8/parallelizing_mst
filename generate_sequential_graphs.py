import matplotlib.pyplot as plt
import numpy as np

# Data for sequential algorithms (time in seconds)
prims_data = {
    'small': {  # 100V, 4000E
        'bubble': 0.000089,
        'quick': 0.000078,
        'merge': 0.003603
    },
    'medium': {  # 1000V, 20000E
        'bubble': 0.002669,
        'quick': 0.002052,
        'merge': 0.002539
    },
    'large': {  # 1500V, 50000E
        'bubble': 0.004842,
        'quick': 0.005730,
        'merge': 0.005349
    }
}

kruskals_data = {
    'small': {  # 100V, 4000E
        'bubble': 0.000547,
        'quick': 0.047843,
        'merge': 0.025280
    },
    'medium': {  # 1000V, 20000E
        'bubble': 0.002880,
        'quick': 1.223023,
        'merge': 0.004899
    },
    'large': {  # 1500V, 50000E
        'bubble': 0.007464,
        'quick': 8.507389,
        'merge': 0.012292
    }
}

def create_comparison_graph(title, filename):
    plt.figure(figsize=(12, 6))
    
    # Set up bar positions
    graph_sizes = ['Small\n(100V, 4000E)', 'Medium\n(1000V, 20000E)', 'Large\n(1500V, 50000E)']
    x = np.arange(len(graph_sizes))
    width = 0.15
    
    # Plot Prim's data
    plt.bar(x - width*2, [prims_data['small']['bubble'], prims_data['medium']['bubble'], prims_data['large']['bubble']], 
            width, label="Prim's - Bubble Sort")
    plt.bar(x - width, [prims_data['small']['quick'], prims_data['medium']['quick'], prims_data['large']['quick']], 
            width, label="Prim's - Quick Sort")
    plt.bar(x, [prims_data['small']['merge'], prims_data['medium']['merge'], prims_data['large']['merge']], 
            width, label="Prim's - Merge Sort")
    
    # Plot Kruskal's data
    plt.bar(x + width, [kruskals_data['small']['bubble'], kruskals_data['medium']['bubble'], kruskals_data['large']['bubble']], 
            width, label="Kruskal's - Bubble Sort")
    plt.bar(x + width*2, [kruskals_data['small']['quick'], kruskals_data['medium']['quick'], kruskals_data['large']['quick']], 
            width, label="Kruskal's - Quick Sort")
    plt.bar(x + width*3, [kruskals_data['small']['merge'], kruskals_data['medium']['merge'], kruskals_data['large']['merge']], 
            width, label="Kruskal's - Merge Sort")
    
    plt.xlabel('Graph Size')
    plt.ylabel('Time (seconds)')
    plt.title(title)
    plt.xticks(x, graph_sizes)
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.grid(True, axis='y')
    plt.tight_layout()
    plt.savefig(filename)
    plt.close()

# Create comparison graph
create_comparison_graph('Sequential MST Algorithm Performance', 'sequential_comparison.png')

# Create separate graphs for each size
sizes = ['small', 'medium', 'large']
size_labels = {
    'small': '100V, 4000E',
    'medium': '1000V, 20000E',
    'large': '1500V, 50000E'
}

for size in sizes:
    plt.figure(figsize=(10, 6))
    algorithms = ['Bubble Sort', 'Quick Sort', 'Merge Sort']
    x = np.arange(len(algorithms))
    width = 0.35
    
    plt.bar(x - width/2, [prims_data[size]['bubble'], prims_data[size]['quick'], prims_data[size]['merge']], 
            width, label="Prim's")
    plt.bar(x + width/2, [kruskals_data[size]['bubble'], kruskals_data[size]['quick'], kruskals_data[size]['merge']], 
            width, label="Kruskal's")
    
    plt.xlabel('Sorting Algorithm')
    plt.ylabel('Time (seconds)')
    plt.title(f'Sequential Performance - {size_labels[size]}')
    plt.xticks(x, algorithms)
    plt.legend()
    plt.grid(True, axis='y')
    plt.tight_layout()
    plt.savefig(f'sequential_{size}.png')
    plt.close() 