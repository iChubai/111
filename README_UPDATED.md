# 多指令集架构下的算法性能交叉比较实验

本实验旨在比较不同算法在不同指令集架构和不同编程语言下的性能表现。

## 实验架构

### 指令集架构
- x86-64（作为基准参考）
- ARM（鲲鹏架构）
- RISC-V
- LoongArch（龙芯架构）

### 编程语言
- C/C++
- Rust（可选）
- Go（可选）

### 算法
- 排序算法：快速排序、归并排序
- 矩阵运算：矩阵乘法
- 密码学算法：AES加密/解密
- 图算法：最短路径（Dijkstra算法）

## 快速开始

### 在单一架构上运行测试

1. 确保已安装GCC编译器：
   ```bash
   which gcc
   ```

2. 运行基准测试脚本：
   ```bash
   cd benchmarks
   ./run_benchmarks.sh <架构>
   ```
   其中`<架构>`可以是：`x86_64`, `arm`, `riscv`, `loongarch`，取决于您当前使用的处理器架构。

3. 查看结果：
   基准测试的结果将保存在`results`目录中，包括：
   - CSV格式的原始数据
   - PNG格式的图表
   - 生成的报告

### 在所有架构上运行测试

1. 使用提供的脚本运行所有架构的测试：
   ```bash
   cd benchmarks
   ./run_all_architectures.sh
   ```

2. 该脚本将：
   - 在当前架构上运行测试
   - 提示您在其他架构上运行测试的命令
   - 当收集到足够的结果后，自动运行比较脚本

3. 在不同架构的机器上运行测试后，将结果文件复制到同一台机器的`results`目录中。

4. 运行比较脚本：
   ```bash
   cd benchmarks
   python3 compare_architectures.py
   ```

5. 查看比较结果：
   比较结果将保存在`results`目录中，包括跨架构比较的图表和表格。

## 添加Rust和Go支持

默认情况下，脚本只运行C语言实现的测试。如果您想添加Rust和Go支持：

1. 安装Rust和Go编译器：
   ```bash
   # 安装Rust
   curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
   source $HOME/.cargo/env

   # 安装Go
   # 下载并安装适合您系统的Go版本
   ```

2. 修改`benchmarks/run_benchmarks.sh`脚本，取消注释Rust和Go相关部分。

## 自定义测试

如果需要调整测试参数（如数组大小、矩阵维度等），可以修改各语言实现中的`main`函数：

- C: `implementations/c/main.c`
- Rust: `implementations/rust/src/main.rs`
- Go: `implementations/go/main.go`

## 故障排除

如果在运行基准测试时遇到问题，请检查以下几点：

1. **编译错误**
   - 确保已安装所有必要的编译器和开发工具
   - 检查各语言的版本兼容性

2. **运行时错误**
   - 确保有足够的内存运行测试（特别是矩阵乘法测试）
   - 对于大型测试，可能需要调整测试参数

3. **结果分析错误**
   - 确保所有必要的Python库已安装：`pip install pandas matplotlib numpy`
   - 检查结果CSV文件格式是否正确

4. **权限问题**
   - 确保基准测试脚本有执行权限：`chmod +x benchmarks/run_benchmarks.sh`
   - 确保有权限创建和写入`results`目录
