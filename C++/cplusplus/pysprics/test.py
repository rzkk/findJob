# Plot the histogram for 'Exited' (customer churn) variable with a more detailed title and labels

import matplotlib.pyplot as plt
plt.figure(figsize=(8, 6))

# Plot the histogram for the 'Exited' variable with custom style
plt.hist(new_data['Exited'], bins=2, color='skyblue', edgecolor='black')

# Adding title and labels as per the given example with more details
plt.title('客户流失情况分布\n大多数客户未流失，少量客户流失', fontsize=16)
plt.xlabel('是否流失（0=未流失, 1=流失）', fontsize=14)
plt.ylabel('客户数量', fontsize=14)

# Set x-axis labels and grid
plt.xticks([0, 1], ['未流失', '流失'])
plt.grid(axis='y', linestyle='--', alpha=0.7)

# Show the plot
plt.show()