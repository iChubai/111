#!/bin/bash

# 检查命令行参数
if [ $# -lt 1 ]; then
    echo "用法: $0 <架构>"
    echo "架构: x86_64, arm, riscv, loongarch"
    exit 1
fi

ARCH=$1
RESULTS_DIR="../results"
mkdir -p $RESULTS_DIR

echo "在 $ARCH 架构上运行基准测试..."

# 编译并运行C实现
echo "编译C实现..."
cd ../implementations/c
make clean
make
./benchmark $ARCH
cd ../../benchmarks

# 编译并运行Rust实现
echo "编译Rust实现..."
cd ../implementations/rust
cargo build --release
./target/release/benchmark $ARCH
cd ../../benchmarks

# 编译并运行Go实现
echo "编译Go实现..."
cd ../implementations/go
go build -o benchmark
./benchmark $ARCH
cd ../../benchmarks

echo "所有基准测试完成！"

# 合并结果
python3 merge_results.py $ARCH

echo "结果已合并到 $RESULTS_DIR/${ARCH}_combined_results.csv"
