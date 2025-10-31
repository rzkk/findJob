import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

# 生成 50 个均匀分布的点作为自变量 X
np.random.seed(42)  # 设置随机种子保证结果可复现
X = np.linspace(0, 10, 50).reshape(-1, 1)  # 50 个点，范围在 0 到 10

# 创建目标值 y，加上一些随机噪声
true_slope = 2.5
true_intercept = 1.0
noise = np.random.normal(loc=0.0, scale=2.0, size=X.shape[0])
y = true_slope * X.flatten() + true_intercept + noise

# 创建并训练线性回归模型
model = LinearRegression()
model.fit(X, y)
y_pred = model.predict(X)

# 输出拟合参数
print("Slope (a):", model.coef_[0])
print("Intercept (b):", model.intercept_)

# 可视化
plt.figure(figsize=(8, 6))
plt.scatter(X, y, color='blue', label='Noisy raw data')
plt.plot(X, y_pred, color='red', linewidth=2, label='Linear regression fit line')
plt.xlabel('X')
plt.ylabel('y')
plt.title('Multi-point linear regression fitting')
plt.legend()
plt.grid(True)
plt.show()
