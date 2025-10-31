import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sns
from sklearn.preprocessing import LabelEncoder

data = pd.read_csv('/mnt/c/Users/rzk/Desktop/Bank-Customer-Attrition-Insights-Data.csv', index_col='RowNumber')
#data.info()
#data.isnull().sum()

#data.describe().T


# 创建LabelEncoder对象
label_encoder = LabelEncoder()# 对Gender列进行标签编码
data['Gender'] = label_encoder.fit_transform(data['Gender'])# 对Geography列进行标签编码
data['Geography'] = label_encoder.fit_transform(data['Geography'])



# 设置画布大小
plt.figure(figsize=(20, 15))
# 1. CreditScore 与流失的关系
plt.subplot(3, 3,1)
sns.boxplot(x='Exited', y='CreditScore',data=data)
plt.title('CreditScore vs Exited')
plt.xlabel('Exited')
plt.ylabel('CreditScore')
# 2. Age 与流失的关系
plt.subplot(3,3,2)
sns.boxplot(x='Exited', y='Age',data=data)
plt.title('Age vs Exited')
plt.xlabel('Exited')
plt.ylabel('Age')
# 3. Balance 与流失的关系
plt.subplot(3,3,3)
sns.boxplot(x='Exited', y='Balance',data=data)
plt.title('Balance vs Exited')
plt.xlabel('Exited')
plt.ylabel('Balance')
# 4. EstimatedSalary 与流失的关系
plt.subplot(3,3,4)
sns.boxplot(x='Exited', y='EstimatedSalary',data=data)
plt.title('EstimatedSalary vs Exited')
plt.xlabel('Exited')
plt.ylabel('EstimatedSalary')
# 5. Geography 与流失的关系
plt.subplot(3,3,5)
sns.countplot(x='Geography', hue='Exited',data=data)
plt.title('Geography vs Exited')
plt.xlabel('Geography')
plt.ylabel('Count')


# 6. Gender 与流失的关系
plt.subplot(3, 3, 6)
sns.countplot(x='Gender', hue='Exited', data=data)
plt.title('Gender vs Exited')
plt.xlabel('Gender')
plt.ylabel('Count')
# 7. NumOfProducts 与流失的关系
plt.subplot(3, 3, 7)
sns.countplot(x='NumOfProducts', hue='Exited', data=data)
plt.title('NumOfProducts vs Exited')
plt.xlabel('NumOfProducts')
plt.ylabel('Count')
# 8. IsActiveMember 与流失的关系
plt.subplot(3, 3, 8)
sns.countplot(x='IsActiveMember', hue='Exited', data=data)
plt.title('IsActiveMember vs Exited')
plt.xlabel('IsActiveMember')
plt.ylabel('Count')
# 9. HasCrCard 与流失的关系
plt.subplot(3, 3, 9)
sns.countplot(x='HasCrCard', hue='Exited', data=data)
plt.title('HasCrCard vs Exited')
plt.xlabel('HasCrCard')
plt.ylabel('Count')

# 调整布局并显示图表
plt.tight_layout()
plt.show()