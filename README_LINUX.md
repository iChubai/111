# 在Linux环境下运行算法性能基准测试

本文档提供了如何在Linux环境下运行算法性能基准测试的说明。

## 准备工作

在运行基准测试之前，请确保您的Linux系统已安装以下软件：

1. **C/C++编译环境**
   - GCC编译器
   - Make工具

   ```bash
   sudo apt-get update
   sudo apt-get install build-essential
   ```

2. **Rust开发环境**
   - Rust编译器和Cargo包管理器

   ```bash
   curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
   source $HOME/.cargo/env
   ```

3. **Go开发环境**
   - Go编译器和工具链

   ```bash
   sudo apt-get install golang
   ```

4. **Python环境**（用于数据分析和可视化）
   - Python 3.6+
   - pandas库
   - matplotlib库
   - numpy库

   ```bash
   sudo apt-get install python3 python3-pip
   pip3 install pandas matplotlib numpy
   ```

## 运行基准测试

1. 确保基准测试脚本有执行权限：

   ```bash
   chmod +x benchmarks/run_benchmarks.sh benchmarks/merge_results.py
   ```

2. 运行基准测试脚本：

   ```bash
   cd benchmarks
   ./run_benchmarks.sh <架构>
   ```

   其中`<架构>`可以是：`x86_64`, `arm`, `riscv`, `loongarch`，取决于您当前使用的处理器架构。

   该脚本将：
   - 编译并运行C实现
   - 编译并运行Rust实现
   - 编译并运行Go实现
   - 合并结果并生成初步图表

3. 查看结果：

   基准测试的结果将保存在`results`目录中，包括：
   - CSV格式的原始数据
   - PNG格式的图表

## 故障排除

如果在运行基准测试时遇到问题，请检查以下几点：

1. **编译错误**
   - 确保已安装所有必要的编译器和开发工具
   - 检查各语言的版本兼容性

2. **运行时错误**
   - 确保有足够的内存运行测试（特别是矩阵乘法测试）
   - 对于大型测试，可能需要调整测试参数

3. **结果分析错误**
   - 确保所有必要的Python库已安装
   - 检查结果CSV文件格式是否正确

4. **权限问题**
   - 确保基准测试脚本有执行权限
   - 确保有权限创建和写入`results`目录

## 自定义测试

如果需要调整测试参数（如数组大小、矩阵维度等），可以修改各语言实现中的`main`函数：

- C: `implementations/c/main.c`
- Rust: `implementations/rust/src/main.rs`
- Go: `implementations/go/main.go`
