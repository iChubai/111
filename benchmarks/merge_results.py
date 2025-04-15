#!/usr/bin/env python3

import sys
import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def merge_results(arch):
    results_dir = "../results"
    
    # 读取各语言的结果文件
    c_results_file = os.path.join(results_dir, f"{arch}_results.csv")
    rust_results_file = os.path.join(results_dir, f"{arch}_results_rust.csv")
    go_results_file = os.path.join(results_dir, f"{arch}_results_go.csv")
    
    # 检查文件是否存在
    files_exist = True
    for file in [c_results_file, rust_results_file, go_results_file]:
        if not os.path.exists(file):
            print(f"警告: 文件 {file} 不存在")
            files_exist = False
    
    if not files_exist:
        print("无法合并结果，某些文件不存在")
        return
    
    # 读取CSV文件
    c_df = pd.read_csv(c_results_file)
    rust_df = pd.read_csv(rust_results_file)
    go_df = pd.read_csv(go_results_file)
    
    # 添加语言列
    c_df['语言'] = 'C'
    rust_df['语言'] = 'Rust'
    go_df['语言'] = 'Go'
    
    # 合并数据框
    combined_df = pd.concat([c_df, rust_df, go_df])
    
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
        languages = test_df['语言'].unique()
        n_languages = len(languages)
        width = 0.35
        x = np.arange(2)  # 两个结果列
        
        # 绘制柱状图
        for i, lang in enumerate(languages):
            lang_df = test_df[test_df['语言'] == lang]
            results = [lang_df['结果1'].values[0], lang_df['结果2'].values[0]]
            plt.bar(x + i*width/n_languages, results, width/n_languages, label=lang)
        
        # 添加标签和标题
        plt.xlabel('算法变体')
        plt.ylabel('执行时间 (微秒)')
        plt.title(f'{arch} 架构上的 {test} 测试')
        plt.xticks(x + width/2, ['变体1', '变体2'])
        plt.legend()
        
        # 保存图表
        plt.savefig(os.path.join(results_dir, f"{arch}_{test}_chart.png"))
        plt.close()
    
    # 创建语言比较图表
    plt.figure(figsize=(15, 10))
    
    # 为每种测试和每种语言计算平均执行时间
    avg_times = {}
    for test in tests:
        avg_times[test] = {}
        test_df = df[df['测试'] == test]
        for lang in languages:
            lang_df = test_df[test_df['语言'] == lang]
            avg_time = (lang_df['结果1'].values[0] + lang_df['结果2'].values[0]) / 2
            avg_times[test][lang] = avg_time
    
    # 设置宽度和位置
    x = np.arange(len(tests))
    width = 0.2
    
    # 绘制柱状图
    for i, lang in enumerate(languages):
        values = [avg_times[test][lang] for test in tests]
        plt.bar(x + i*width, values, width, label=lang)
    
    # 添加标签和标题
    plt.xlabel('测试类型')
    plt.ylabel('平均执行时间 (微秒)')
    plt.title(f'{arch} 架构上不同语言的性能比较')
    plt.xticks(x + width, tests)
    plt.legend()
    
    # 保存图表
    plt.savefig(os.path.join(results_dir, f"{arch}_language_comparison.png"))
    plt.close()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("用法: python merge_results.py <架构>")
        sys.exit(1)
    
    arch = sys.argv[1]
    merge_results(arch)
