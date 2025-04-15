#!/usr/bin/env python3

import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def compare_architectures(archs):
    results_dir = "../results"
    
    # 检查每个架构的合并结果文件是否存在
    dfs = {}
    for arch in archs:
        file_path = os.path.join(results_dir, f"{arch}_combined_results.csv")
        if os.path.exists(file_path):
            dfs[arch] = pd.read_csv(file_path)
        else:
            print(f"警告: 文件 {file_path} 不存在")
    
    if not dfs:
        print("没有可用的结果文件进行比较")
        return
    
    # 获取所有测试和语言
    all_tests = set()
    all_languages = set()
    for df in dfs.values():
        all_tests.update(df['测试'].unique())
        all_languages.update(df['语言'].unique())
    
    all_tests = sorted(list(all_tests))
    all_languages = sorted(list(all_languages))
    
    # 为每种测试和语言组合创建架构比较图表
    for test in all_tests:
        for lang in all_languages:
            plt.figure(figsize=(12, 8))
            
            # 收集数据
            arch_data = {}
            for arch, df in dfs.items():
                filtered_df = df[(df['测试'] == test) & (df['语言'] == lang)]
                if not filtered_df.empty:
                    arch_data[arch] = [filtered_df['结果1'].values[0], filtered_df['结果2'].values[0]]
            
            if not arch_data:
                plt.close()
                continue
            
            # 设置宽度和位置
            x = np.arange(2)  # 两个结果列
            width = 0.8 / len(arch_data)
            
            # 绘制柱状图
            for i, (arch, results) in enumerate(arch_data.items()):
                plt.bar(x + i*width, results, width, label=arch)
            
            # 添加标签和标题
            plt.xlabel('算法变体')
            plt.ylabel('执行时间 (微秒)')
            plt.title(f'{lang} 语言的 {test} 测试在不同架构上的比较')
            plt.xticks(x + width*len(arch_data)/2, ['变体1', '变体2'])
            plt.legend()
            
            # 保存图表
            plt.savefig(os.path.join(results_dir, f"{test}_{lang}_arch_comparison.png"))
            plt.close()
    
    # 创建架构总体比较图表
    plt.figure(figsize=(15, 10))
    
    # 为每种架构、测试和语言计算平均执行时间
    avg_times = {}
    for arch, df in dfs.items():
        avg_times[arch] = {}
        for test in all_tests:
            avg_times[arch][test] = {}
            for lang in all_languages:
                filtered_df = df[(df['测试'] == test) & (df['语言'] == lang)]
                if not filtered_df.empty:
                    avg_time = (filtered_df['结果1'].values[0] + filtered_df['结果2'].values[0]) / 2
                    avg_times[arch][test][lang] = avg_time
    
    # 计算每种架构的总体平均时间
    overall_avg = {}
    for arch in archs:
        if arch in avg_times:
            times = []
            for test in all_tests:
                if test in avg_times[arch]:
                    for lang in all_languages:
                        if lang in avg_times[arch][test]:
                            times.append(avg_times[arch][test][lang])
            if times:
                overall_avg[arch] = sum(times) / len(times)
    
    # 设置宽度和位置
    x = np.arange(len(overall_avg))
    width = 0.6
    
    # 绘制柱状图
    plt.bar(x, list(overall_avg.values()), width)
    
    # 添加标签和标题
    plt.xlabel('架构')
    plt.ylabel('平均执行时间 (微秒)')
    plt.title('不同架构的总体性能比较')
    plt.xticks(x, list(overall_avg.keys()))
    
    # 保存图表
    plt.savefig(os.path.join(results_dir, "architecture_overall_comparison.png"))
    plt.close()
    
    # 创建指令集特性比较表
    create_instruction_set_comparison(archs, results_dir)

def create_instruction_set_comparison(archs, results_dir):
    # 指令集特性比较
    features = {
        'x86_64': {
            '架构类型': 'CISC',
            '字长': '64位',
            '寄存器数量': '16个通用寄存器',
            'SIMD支持': 'SSE, AVX, AVX-512',
            '内存模型': '弱一致性',
            '特殊指令': 'x86指令集扩展',
            '功耗特性': '较高功耗',
            '主要应用': '服务器、桌面计算机'
        },
        'arm': {
            '架构类型': 'RISC',
            '字长': '64位 (AArch64)',
            '寄存器数量': '31个通用寄存器',
            'SIMD支持': 'NEON',
            '内存模型': '弱一致性',
            '特殊指令': 'SVE (鲲鹏特性)',
            '功耗特性': '低功耗',
            '主要应用': '移动设备、服务器'
        },
        'riscv': {
            '架构类型': 'RISC',
            '字长': '32/64位',
            '寄存器数量': '32个通用寄存器',
            'SIMD支持': 'V扩展',
            '内存模型': '弱一致性',
            '特殊指令': '模块化扩展',
            '功耗特性': '可配置',
            '主要应用': '嵌入式系统、IoT设备'
        },
        'loongarch': {
            '架构类型': 'RISC',
            '字长': '64位',
            '寄存器数量': '32个通用寄存器',
            'SIMD支持': 'LSX, LASX',
            '内存模型': '弱一致性',
            '特殊指令': '二进制翻译扩展',
            '功耗特性': '中等功耗',
            '主要应用': '服务器、工作站'
        }
    }
    
    # 创建比较表
    comparison_data = []
    for feature in features['x86_64'].keys():
        row = {'特性': feature}
        for arch in archs:
            if arch in features:
                row[arch] = features[arch].get(feature, 'N/A')
        comparison_data.append(row)
    
    comparison_df = pd.DataFrame(comparison_data)
    
    # 保存比较表
    comparison_file = os.path.join(results_dir, "instruction_set_comparison.csv")
    comparison_df.to_csv(comparison_file, index=False)
    
    # 创建HTML表格以便更好地可视化
    html_file = os.path.join(results_dir, "instruction_set_comparison.html")
    with open(html_file, 'w') as f:
        f.write('<html><head><style>')
        f.write('table { border-collapse: collapse; width: 100%; }')
        f.write('th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }')
        f.write('th { background-color: #f2f2f2; }')
        f.write('tr:nth-child(even) { background-color: #f9f9f9; }')
        f.write('</style></head><body>')
        f.write('<h1>指令集架构特性比较</h1>')
        f.write('<table>')
        
        # 表头
        f.write('<tr><th>特性</th>')
        for arch in archs:
            if arch in features:
                f.write(f'<th>{arch}</th>')
        f.write('</tr>')
        
        # 表内容
        for feature in features['x86_64'].keys():
            f.write(f'<tr><td>{feature}</td>')
            for arch in archs:
                if arch in features:
                    f.write(f'<td>{features[arch].get(feature, "N/A")}</td>')
            f.write('</tr>')
        
        f.write('</table>')
        f.write('</body></html>')

if __name__ == "__main__":
    # 指定要比较的架构
    architectures = ['x86_64', 'arm', 'riscv', 'loongarch']
    compare_architectures(architectures)
