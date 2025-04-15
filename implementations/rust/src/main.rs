mod sorting;
mod matrix;
mod crypto;
mod graph;

use std::env;
use std::fs::OpenOptions;
use std::io::Write;
use std::time::Instant;

// 排序算法测试
fn test_sorting(size: usize) -> [u128; 2] {
    println!("测试排序算法 (数组大小: {})...", size);
    
    // 生成随机数组
    let mut arr1 = vec![0; size];
    let mut arr2 = vec![0; size];
    
    // 初始化随机数组
    for i in 0..size {
        arr1[i] = rand::random::<i32>() % 10000;
        arr2[i] = arr1[i]; // 复制相同的数组用于不同算法
    }
    
    // 测试快速排序
    let start_time = Instant::now();
    sorting::quicksort(&mut arr1, 0, (size - 1) as isize);
    let quicksort_time = start_time.elapsed().as_micros();
    println!("快速排序耗时: {:.6} 秒", quicksort_time as f64 / 1_000_000.0);
    
    // 测试归并排序
    let start_time = Instant::now();
    sorting::mergesort(&mut arr2, 0, (size - 1) as isize);
    let mergesort_time = start_time.elapsed().as_micros();
    println!("归并排序耗时: {:.6} 秒", mergesort_time as f64 / 1_000_000.0);
    
    [quicksort_time, mergesort_time]
}

// 矩阵乘法测试
fn test_matrix(size: usize) -> [u128; 2] {
    println!("测试矩阵乘法 (矩阵大小: {} x {})...", size, size);
    
    // 创建并初始化矩阵
    let a = matrix::initialize_matrix(size);
    let b = matrix::initialize_matrix(size);
    
    // 测试标准矩阵乘法
    let start_time = Instant::now();
    let _c = matrix::matrix_multiply(&a, &b);
    let standard_time = start_time.elapsed().as_micros();
    println!("标准矩阵乘法耗时: {:.6} 秒", standard_time as f64 / 1_000_000.0);
    
    // 测试分块矩阵乘法
    let block_size = 32; // 可调整块大小
    let start_time = Instant::now();
    let _c = matrix::matrix_multiply_blocked(&a, &b, block_size);
    let blocked_time = start_time.elapsed().as_micros();
    println!("分块矩阵乘法耗时: {:.6} 秒", blocked_time as f64 / 1_000_000.0);
    
    [standard_time, blocked_time]
}

// AES加密测试
fn test_aes(size: usize) -> [u128; 2] {
    println!("测试AES加密 (数据大小: {} 字节)...", size);
    
    // 确保数据大小是AES块大小的倍数
    let block_size = 16; // AES块大小
    let size = if size % block_size != 0 {
        (size / block_size + 1) * block_size
    } else {
        size
    };
    
    // 生成随机数据
    let data = crypto::generate_random_data(size);
    let key = crypto::generate_random_data(16); // AES-128
    let iv = crypto::generate_random_data(16);
    
    // 测试AES-CBC加密
    let start_time = Instant::now();
    let encrypted = crypto::aes_encrypt(&data, &key, &iv);
    let encrypt_time = start_time.elapsed().as_micros();
    println!("AES-CBC加密耗时: {:.6} 秒", encrypt_time as f64 / 1_000_000.0);
    
    // 测试AES-CBC解密
    let start_time = Instant::now();
    let decrypted = crypto::aes_decrypt(&encrypted, &key, &iv);
    let decrypt_time = start_time.elapsed().as_micros();
    println!("AES-CBC解密耗时: {:.6} 秒", decrypt_time as f64 / 1_000_000.0);
    
    // 验证解密结果
    let correct = data == decrypted;
    println!("解密验证: {}", if correct { "成功" } else { "失败" });
    
    [encrypt_time, decrypt_time]
}

// Dijkstra算法测试
fn test_dijkstra(vertices: usize, edges: usize) -> [u128; 2] {
    println!("测试Dijkstra算法 (顶点数: {}, 边数: {})...", vertices, edges);
    
    // 创建图
    let mut g = graph::Graph::new(vertices);
    
    // 随机添加边
    for _ in 0..edges {
        let src = rand::random::<usize>() % vertices;
        let dest = rand::random::<usize>() % vertices;
        let weight = 1 + rand::random::<i32>() % 100; // 权重范围1-100
        
        if src != dest { // 避免自环
            g.add_edge(src, dest, weight);
        }
    }
    
    // 选择源顶点
    let src = 0;
    
    // 测试标准Dijkstra算法
    let start_time = Instant::now();
    let (dist1, _prev1) = g.dijkstra(src);
    let standard_time = start_time.elapsed().as_micros();
    println!("标准Dijkstra算法耗时: {:.6} 秒", standard_time as f64 / 1_000_000.0);
    
    // 测试优化的Dijkstra算法
    let start_time = Instant::now();
    let (dist2, _prev2) = g.dijkstra_optimized(src);
    let optimized_time = start_time.elapsed().as_micros();
    println!("优化的Dijkstra算法耗时: {:.6} 秒", optimized_time as f64 / 1_000_000.0);
    
    // 验证两种算法结果是否一致
    let correct = dist1 == dist2;
    println!("算法验证: {}", if correct { "成功" } else { "失败" });
    
    [standard_time, optimized_time]
}

// 将结果写入文件
fn write_results(filename: &str, arch: &str, test_name: &str, results: &[u128]) {
    let mut file = OpenOptions::new()
        .write(true)
        .append(true)
        .create(true)
        .open(filename)
        .expect("无法打开结果文件");
    
    // 写入结果
    let mut line = format!("{},{}", arch, test_name);
    for result in results {
        line.push_str(&format!(",{}", result));
    }
    line.push('\n');
    
    file.write_all(line.as_bytes()).expect("写入结果失败");
}

fn main() {
    // 获取命令行参数
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("用法: {} <架构>", args[0]);
        println!("架构: x86_64, arm, riscv, loongarch");
        return;
    }
    
    let arch = &args[1];
    let results_file = format!("../../results/{}_results_rust.csv", arch);
    
    // 创建或清空结果文件
    let mut file = OpenOptions::new()
        .write(true)
        .create(true)
        .truncate(true)
        .open(&results_file)
        .expect("无法创建结果文件");
    
    // 写入CSV头
    file.write_all(b"架构,测试,结果1,结果2\n").expect("写入CSV头失败");
    
    // 测试参数
    let sorting_size = 100000;
    let matrix_size = 500;
    let aes_size = 1024 * 1024; // 1MB
    let graph_vertices = 1000;
    let graph_edges = 10000;
    
    // 运行排序测试
    let results = test_sorting(sorting_size);
    write_results(&results_file, arch, "排序", &results);
    
    // 运行矩阵乘法测试
    let results = test_matrix(matrix_size);
    write_results(&results_file, arch, "矩阵", &results);
    
    // 运行AES加密测试
    let results = test_aes(aes_size);
    write_results(&results_file, arch, "AES", &results);
    
    // 运行Dijkstra算法测试
    let results = test_dijkstra(graph_vertices, graph_edges);
    write_results(&results_file, arch, "Dijkstra", &results);
    
    println!("测试完成，结果已写入 {}", results_file);
}
