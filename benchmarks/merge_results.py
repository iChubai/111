#!/usr/bin/env python3

import sys
import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def merge_results(arch):
    results_dir = "../results"

    # 读取C语言的结果文件
    c_results_file = os.path.join(results_dir, f"{arch}_results.csv")

    # 检查文件是否存在
    if not os.path.exists(c_results_file):
        print(f"警告: 文件 {c_results_file} 不存在")
        print("无法合并结果，结果文件不存在")
        return

    # 读取CSV文件
    c_df = pd.read_csv(c_results_file)

    # 添加语言列
    c_df['语言'] = 'C'

    # 使用C语言的结果作为合并结果
    combined_df = c_df.copy()

    # 保存合并结果
    combined_file = os.path.join(results_dir, f"{arch}_combined_results.csv")
    combined_df.to_csv(combined_file, index=False)

    # 生成图表
    generate_charts(combined_df, arch, results_dir)

def generate_charts(df, arch, results_dir):
    # 为每种测试创建一个图表
    tests = df['测试'].unique()

    for test in tests:
        test_df = df[df['测试'] == test]

        # 创建图表
        plt.figure(figsize=(12, 8))

        # 设置宽度和位置
        width = 0.35
        x = np.arange(2)  # 两个结果列

        # 绘制柱状图
        results = [test_df['结果1'].values[0], test_df['结果2'].values[0]]
        plt.bar(x, results, width, label='C')

        # 添加标签和标题
        plt.xlabel('算法变体')
        plt.ylabel('执行时间 (微秒)')
        plt.title(f'{arch} 架构上的 {test} 测试')
        plt.xticks(x, ['变体1', '变体2'])
        plt.legend()

        # 保存图表
        plt.savefig(os.path.join(results_dir, f"{arch}_{test}_chart.png"))
        plt.close()

    # 创建测试比较图表
    plt.figure(figsize=(15, 10))

    # 为每种测试计算平均执行时间
    avg_times = {}
    for test in tests:
        test_df = df[df['测试'] == test]
        avg_time = (test_df['结果1'].values[0] + test_df['结果2'].values[0]) / 2
        avg_times[test] = avg_time

    # 设置宽度和位置
    x = np.arange(len(tests))
    width = 0.5

    # 绘制柱状图
    values = [avg_times[test] for test in tests]
    plt.bar(x, values, width)

    # 添加标签和标题
    plt.xlabel('测试类型')
    plt.ylabel('平均执行时间 (微秒)')
    plt.title(f'{arch} 架构上的性能比较')
    plt.xticks(x, tests)

    # 保存图表
    plt.savefig(os.path.join(results_dir, f"{arch}_test_comparison.png"))
    plt.close()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("用法: python merge_results.py <架构>")
        sys.exit(1)

    arch = sys.argv[1]
    merge_results(arch)
