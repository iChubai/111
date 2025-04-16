import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# 读取CSV文件
data = pd.read_csv('results/x86_64_results.csv', skiprows=[0, 1, 2, 3, 4], header=None)
data.columns = ['架构', '测试类型', '算法1', '算法2', '算法3', '算法4', '算法5', '算法6']

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

# 创建一个图形对象，设置大小
plt.figure(figsize=(15, 12))

# 1. 排序算法性能比较
plt.subplot(2, 2, 1)
sorting_data = data[data['测试类型'] == '排序'].iloc[0, 2:8].astype(float).values
sorting_labels = ['快速排序', '归并排序', '堆排序', 'Shell排序', '基数排序', '计数排序']
colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#9467bd', '#8c564b']

# 创建条形图
bars = plt.bar(sorting_labels, sorting_data, color=colors)

# 在条形上方添加数值标签
for bar in bars:
    height = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2., height + 0.1,
             f'{int(height)}',
             ha='center', va='bottom', rotation=0)

plt.title('排序算法性能比较 (微秒)', fontsize=14)
plt.ylabel('执行时间 (微秒)', fontsize=12)
plt.xticks(rotation=45, ha='right')
plt.grid(axis='y', linestyle='--', alpha=0.7)

# 2. 矩阵算法性能比较
plt.subplot(2, 2, 2)
matrix_data = data[data['测试类型'] == '矩阵'].iloc[0, 2:8].astype(float).values
matrix_labels = ['标准乘法', '分块乘法', 'Strassen乘法', '矩阵转置', 'LU分解', '矩阵求逆']
colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#9467bd', '#8c564b']

# 创建条形图
bars = plt.bar(matrix_labels, matrix_data, color=colors)

# 在条形上方添加数值标签
for bar in bars:
    height = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2., height + 0.1,
             f'{int(height)}',
             ha='center', va='bottom', rotation=0)

plt.title('矩阵算法性能比较 (微秒)', fontsize=14)
plt.ylabel('执行时间 (微秒)', fontsize=12)
plt.xticks(rotation=45, ha='right')
plt.grid(axis='y', linestyle='--', alpha=0.7)

# 3. AES加密解密性能比较
plt.subplot(2, 2, 3)
aes_data = data[data['测试类型'] == 'AES'].iloc[0, 2:4].astype(float).values
aes_labels = ['加密', '解密']
colors = ['#1f77b4', '#ff7f0e']

# 创建条形图
bars = plt.bar(aes_labels, aes_data, color=colors)

# 在条形上方添加数值标签
for bar in bars:
    height = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2., height + 0.1,
             f'{int(height)}',
             ha='center', va='bottom', rotation=0)

plt.title('AES加密解密性能比较 (微秒)', fontsize=14)
plt.ylabel('执行时间 (微秒)', fontsize=12)
plt.grid(axis='y', linestyle='--', alpha=0.7)

# 4. Dijkstra算法性能比较
plt.subplot(2, 2, 4)
dijkstra_data = data[data['测试类型'] == 'Dijkstra'].iloc[0, 2:4].astype(float).values
dijkstra_labels = ['标准算法', '优化算法']
colors = ['#1f77b4', '#ff7f0e']

# 创建条形图
bars = plt.bar(dijkstra_labels, dijkstra_data, color=colors)

# 在条形上方添加数值标签
for bar in bars:
    height = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2., height + 0.1,
             f'{int(height)}',
             ha='center', va='bottom', rotation=0)

plt.title('Dijkstra算法性能比较 (微秒)', fontsize=14)
plt.ylabel('执行时间 (微秒)', fontsize=12)
plt.grid(axis='y', linestyle='--', alpha=0.7)

# 调整布局
plt.tight_layout()

# 保存图表
plt.savefig('results/benchmark_visualization.png', dpi=300)
print("可视化图表已保存到 results/benchmark_visualization.png")
