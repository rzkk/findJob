import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from sklearn.linear_model import LinearRegression

# 随机生成数据
np.random.seed(42)
x1 = np.random.uniform(0, 10, 50)
x2 = np.random.uniform(0, 10, 50)
noise = np.random.normal(0, 2, 50)
y = 3 * x1 + 2 * x2 + 5 + noise

# 合并特征
X = np.column_stack((x1, x2))

# 拟合线性回归模型
model = LinearRegression()
model.fit(X, y)

# 输出模型参数
print("系数 a1, a2:", model.coef_)
print("截距 b:", model.intercept_)

# 预测值
y_pred = model.predict(X)

# 创建3D图形
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# 绘制原始数据点
ax.scatter(x1, x2, y, color='blue', label='原始数据')

# 创建平面网格
x1_grid, x2_grid = np.meshgrid(
    np.linspace(x1.min(), x1.max(), 20),
    np.linspace(x2.min(), x2.max(), 20)
)
X_grid = np.column_stack((x1_grid.ravel(), x2_grid.ravel()))
y_grid = model.predict(X_grid).reshape(x1_grid.shape)

# 绘制拟合平面（去掉 label）
ax.plot_surface(x1_grid, x2_grid, y_grid, color='red', alpha=0.5)

# 设置标签
ax.set_xlabel('x1')
ax.set_ylabel('x2')
ax.set_zlabel('y')
ax.set_title('多元线性回归三维图')

# 添加图例（仅为散点图）
ax.legend()
plt.tight_layout()
plt.show()
