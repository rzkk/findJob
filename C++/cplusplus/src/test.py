import pandas as pd
import matplotlib.pyplot as plt

# 1. 准备数据
data = {
    'name': ['Alexander', 'Ralph', 'Christian', 'Leonid', 'Keith', 'Roman'],
    'Below 9 rings': [1, 1, 1, 1, 2, 2],
    '9~10 rings': [9, 9, 8, 11, 13, 10],
    'More than 10 rings': [10, 10, 11, 8, 5, 8]
}
df = pd.DataFrame(data)

# 2. 设置颜色和标签
colors = ['#FF6B6B', '#FFD166', '#06D6A0']  # 红、黄、绿
labels = ['Below 9 rings', '9~10 rings', 'More than 10 rings']

# 3. 绘制堆叠柱状图
plt.figure(figsize=(10, 6))
bottom = None  # 用于堆叠的基准

for i, col in enumerate(df.columns[1:]):
    plt.bar(
        df['name'], 
        df[col], 
        bottom=bottom, 
        color=colors[i], 
        label=labels[i],
        edgecolor='white'
    )
    if bottom is None:
        bottom = df[col]
    else:
        bottom += df[col]

# 4. 添加图表标题和标签
plt.title('Results of the mens 25m rapid-fire pistol finals at the Olympics', fontsize=14, pad=20)
plt.xlabel('Athlete Name', fontsize=12)
plt.ylabel('Number of shots (20 shots)', fontsize=12)
plt.legend(title='Ring number interval', bbox_to_anchor=(1.05, 1), loc='upper left')

# 5. 显示数值标签
for name in df['name']:
    total = df[df['name'] == name].iloc[:, 1:].sum(axis=1).values[0]
    plt.text(
        name, total + 0.5, f'Total times: {total}', 
        ha='center', va='bottom', fontsize=10
    )

plt.tight_layout()  # 调整布局
plt.show()

# 6. 保存图表（可选）
# plt.savefig('决赛成绩分布.png', dpi=300, bbox_inches='tight')