#!/bin/bash

# 这个脚本用于在所有支持的架构上运行基准测试
# 使用方法: ./run_all_architectures.sh

# 定义支持的架构
ARCHITECTURES=("x86_64" "arm" "riscv" "loongarch")

# 创建结果目录
RESULTS_DIR="../results"
mkdir -p $RESULTS_DIR

# 为每个架构运行基准测试
for arch in "${ARCHITECTURES[@]}"; do
    echo "====================================="
    echo "开始在 $arch 架构上运行基准测试..."
    echo "====================================="
    
    # 检查当前系统架构
    current_arch=$(uname -m)
    
    if [ "$current_arch" == "$arch" ]; then
        # 如果当前架构匹配，直接运行测试
        echo "当前系统架构是 $arch，直接运行测试"
        ./run_benchmarks.sh $arch
    else
        # 如果当前架构不匹配，提示用户
        echo "当前系统架构是 $current_arch，不是 $arch"
        echo "请在 $arch 架构的系统上运行以下命令："
        echo "cd $(pwd) && ./run_benchmarks.sh $arch"
        echo "然后将结果文件复制到 $RESULTS_DIR 目录"
    fi
    
    echo ""
done

# 检查是否有足够的结果文件进行比较
echo "检查结果文件..."
result_count=0
for arch in "${ARCHITECTURES[@]}"; do
    if [ -f "$RESULTS_DIR/${arch}_combined_results.csv" ]; then
        echo "找到 $arch 的结果文件"
        ((result_count++))
    else
        echo "未找到 $arch 的结果文件"
    fi
done

# 如果有多个架构的结果，运行比较脚本
if [ $result_count -gt 1 ]; then
    echo "找到多个架构的结果，运行比较脚本..."
    cd ..
    python3 benchmarks/compare_architectures.py
    echo "比较完成，结果保存在 $RESULTS_DIR 目录"
else
    echo "没有足够的架构结果进行比较（至少需要2个）"
    echo "请在其他架构上运行测试，然后再次运行此脚本"
fi
