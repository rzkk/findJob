import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sns
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.metrics import classification_report, roc_curve, auc, confusion_matrix, RocCurveDisplay
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier, GradientBoostingClassifier
from sklearn.svm import SVC
import matplotlib.pyplot as plt

from scipy.stats import chi2_contingency, ttest_ind
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split

data = pd.read_csv('/mnt/c/Users/rzk/Desktop/Bank-Customer-Attrition-Insights-Data.csv', index_col='RowNumber')
#data.info()
#data.isnull().sum()

#data.describe().T


# 创建LabelEncoder对象
label_encoder = LabelEncoder()# 对Gender列进行标签编码
data['Gender'] = label_encoder.fit_transform(data['Gender'])# 对Geography列进行标签编码
data['Geography'] = label_encoder.fit_transform(data['Geography'])

# 数据准备
X = data.drop(columns=['Exited', 'CustomerId', 'Surname', 'Complain']) # 移除无关或强相关列
X = pd.get_dummies(X, drop_first=True) # 对分类变量进行独热编码
y = data['Exited']
# **1. Point-Biserial相关系数（适用于数值型变量）**
numerical_columns = ['CreditScore', 'Age', 'Balance', 'EstimatedSalary', 'Tenure', 'Point Earned']
point_biserial_corr = X[numerical_columns].corrwith(y)


# 2. 卡方检验（针对分类变量）
from sklearn.feature_selection import chi2
categorical_features = ['Gender', 'Geography', 'HasCrCard', 'IsActiveMember', 'NumOfProducts']
chi_scores, p_values = chi2(X[categorical_features], y)
chi2_results = pd.DataFrame({
    'Feature': categorical_features, 
    'Chi2 Score': chi_scores,
    'P-Value': p_values
}).sort_values(by='Chi2 Score', ascending=False)


# 3. t检验（针对数值型变量）
numerical_features = X.select_dtypes(include=['float64', 'int64']).columns
t_test_results = []
for feature in numerical_features: 
    group0 = data[data['Exited'] == 0][feature]
    group1 = data[data['Exited'] == 1][feature] 
    t_stat, p_val = ttest_ind(group0, group1, equal_var=False)
    t_test_results.append((feature, t_stat, p_val))
t_test_results_df = pd.DataFrame(t_test_results, columns=['Feature', 'T-Statistic', 'P-Value']).sort_values(by='P-Value')


# 4. 特征重要性（随机森林）
rf = RandomForestClassifier(random_state=42)
rf.fit(X, y)
feature_importance = pd.DataFrame({
    'Feature': X.columns,
    'Importance': rf.feature_importances_}).sort_values(by='Importance', ascending=False)




X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# 定义模型
models = {"Logistic Regression": LogisticRegression(max_iter=1000, random_state=42),
          "Decision Tree": DecisionTreeClassifier(random_state=42),
          "Random Forest": RandomForestClassifier(random_state=42),
          "Gradient Boosting (GBM)": GradientBoostingClassifier(random_state=42),
          "SVM": SVC(probability=True, random_state=42)}

# # 模型训练与评估
# report = classification_report(y_test, y_pred, output_dict=True, zero_division=0)

# results = []
# for model_name, model in models.items(): # 交叉验证得分   
#     cv_scores = cross_val_score(model, X_train, y_train, cv=5, scoring='accuracy')
#     # 模型训练    
#     model.fit(X_train, y_train)
#      # 测试集预测    
#     y_pred = model.predict(X_test)
#     y_pred_prob = model.predict_proba(X_test)[:, 1] if hasattr(model, "predict_proba") else None
#     # 评估指标    
     
#     report = classification_report(y_test, y_pred, output_dict=True)
#     results.append({
#         "Model": model_name,
#         "Accuracy": report['accuracy'],
#         "Recall": report['1']['recall'],
#         "F1-Score": report['1']['f1-score'],
#         "Cross-Validation Accuracy": cv_scores.mean() })# 绘制ROC曲线 
#     if y_pred_prob is not None:
#         fpr, tpr, _ = roc_curve(y_test, y_pred_prob)
#         roc_auc = auc(fpr, tpr)
#         RocCurveDisplay(fpr=fpr, tpr=tpr, roc_auc=roc_auc, estimator_name=model_name).plot()
#         plt.title(f"ROC Curve - {model_name}")

# 模型训练与评估
results = []
for model_name, model in models.items():
    # 交叉验证得分
    cv_scores = cross_val_score(model, X_train, y_train, cv=5, scoring='accuracy')
    # 模型训练
    model.fit(X_train, y_train)
    # 测试集预测
    y_pred = model.predict(X_test)
    y_pred_prob = model.predict_proba(X_test)[:, 1] if hasattr(model, "predict_proba") else None
    # 评估指标，添加zero_division=0防止警告
    report = classification_report(y_test, y_pred, output_dict=True, zero_division=0)
    results.append({
        "Model": model_name,
        "Accuracy": report['accuracy'],
        "Recall": report['1']['recall'],
        "F1-Score": report['1']['f1-score'],
        "Cross-Validation Accuracy": cv_scores.mean()
    })

    # 绘制ROC曲线
    if y_pred_prob is not None:
        fpr, tpr, _ = roc_curve(y_test, y_pred_prob)
        roc_auc = auc(fpr, tpr)
        RocCurveDisplay(fpr=fpr, tpr=tpr, roc_auc=roc_auc, estimator_name=model_name).plot()
        plt.title(f"ROC Curve - {model_name}")
        plt.show()
