# 多指令集架构下的算法性能交叉比较实验说明

本文档提供了如何在不同指令集架构上运行实验的详细说明。

## 实验准备

### 所需环境

为了完成本实验，您需要访问以下指令集架构的计算环境：

1. **x86_64** - 常见的Intel或AMD处理器
2. **ARM (鲲鹏)** - 华为鲲鹏处理器或其他ARM架构处理器
3. **RISC-V** - RISC-V架构处理器
4. **LoongArch** - 龙芯处理器

### 软件要求

在每个架构上，您需要安装以下软件：

1. **C/C++编译环境**
   - GCC编译器
   - Make工具

2. **Rust开发环境**
   - Rust编译器和Cargo包管理器
   - 可通过rustup安装：`curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh`

3. **Go开发环境**
   - Go编译器和工具链

4. **Python环境**（用于数据分析和可视化）
   - Python 3.6+
   - pandas库：`pip install pandas`
   - matplotlib库：`pip install matplotlib`
   - numpy库：`pip install numpy`

## 实验步骤

### 1. 克隆实验代码

```bash
git clone <repository-url>
cd Lab2
```

### 2. 在每个架构上运行基准测试

对于每个指令集架构，执行以下步骤：

1. 登录到相应架构的机器
2. 进入实验目录
3. 运行基准测试脚本

```bash
cd benchmarks
chmod +x run_benchmarks.sh
./run_benchmarks.sh <架构>
```

其中`<架构>`可以是：`x86_64`, `arm`, `riscv`, `loongarch`

该脚本将：
- 编译并运行C实现
- 编译并运行Rust实现
- 编译并运行Go实现
- 合并结果并生成初步图表

### 3. 收集所有架构的结果

在所有架构上完成测试后，将所有结果文件收集到同一台机器上的`results`目录中。

### 4. 比较不同架构的结果

```bash
cd benchmarks
python3 compare_architectures.py
```

这将生成跨架构比较的图表和表格。

### 5. 生成实验报告

使用`results/report_template.md`作为模板，填写实验结果和分析，生成最终的实验报告。

## 实验定制

### 修改测试参数

如果需要调整测试参数（如数组大小、矩阵维度等），可以修改各语言实现中的`main`函数：

- C: `implementations/c/main.c`
- Rust: `implementations/rust/src/main.rs`
- Go: `implementations/go/main.go`

### 添加新算法

要添加新的算法测试，需要：

1. 在`algorithms`目录下创建新的头文件
2. 在各语言实现中添加相应的实现
3. 修改主程序以包含新的测试

### 添加新的指令集架构

要添加新的指令集架构，只需在新架构上运行基准测试脚本，并将结果添加到比较中。

## 故障排除

### 编译问题

- 确保已安装所有必要的编译器和开发工具
- 检查各语言的版本兼容性

### 运行问题

- 确保有足够的内存运行测试（特别是矩阵乘法测试）
- 对于大型测试，可能需要调整测试参数

### 结果分析问题

- 确保所有必要的Python库已安装
- 检查结果CSV文件格式是否正确
