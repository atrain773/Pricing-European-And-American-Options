import matplotlib.pyplot as plt
import csv

# Define the file path
file_path = 'plot/convergence.csv'  # Replace with your actual file path

# Initialize lists to store data
x = []
y = []

# Read the data from the file
with open(file_path, 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        x.append(float(row[0]))  # First column as X-axis
        y.append(float(row[1]))  # Second column as Y-axis

# Plot the data
plt.figure(figsize=(10, 6))
plt.plot(x, y, marker='o', label='CRR Binomial Model')
plt.title('CRR Binomial Model Convergence')
plt.axhline(y = 8.10264, color = 'r', linestyle = '-', label = 'Black Scholes') 
plt.legend()
plt.xlabel('# of Steps(N)')
plt.ylabel('Price ($)')
plt.grid(True)
# plt.show()
plt.savefig('plot/plot.png')
