package main

import (
	"algorithm_benchmark/sorting"
	"algorithm_benchmark/matrix"
	"algorithm_benchmark/crypto"
	"algorithm_benchmark/graph"
	"fmt"
	"math/rand"
	"os"
	"time"
)

// 排序算法测试
func testSorting(size int) [2]int64 {
	fmt.Printf("测试排序算法 (数组大小: %d)...\n", size)
	
	// 生成随机数组
	arr1 := make([]int, size)
	arr2 := make([]int, size)
	
	// 初始化随机数组
	rand.Seed(time.Now().UnixNano())
	for i := 0; i < size; i++ {
		arr1[i] = rand.Intn(10000)
		arr2[i] = arr1[i] // 复制相同的数组用于不同算法
	}
	
	// 测试快速排序
	startTime := time.Now()
	sorting.Quicksort(arr1, 0, size-1)
	quicksortTime := time.Since(startTime).Microseconds()
	fmt.Printf("快速排序耗时: %.6f 秒\n", float64(quicksortTime)/1000000.0)
	
	// 测试归并排序
	startTime = time.Now()
	sorting.Mergesort(arr2, 0, size-1)
	mergesortTime := time.Since(startTime).Microseconds()
	fmt.Printf("归并排序耗时: %.6f 秒\n", float64(mergesortTime)/1000000.0)
	
	return [2]int64{quicksortTime, mergesortTime}
}

// 矩阵乘法测试
func testMatrix(size int) [2]int64 {
	fmt.Printf("测试矩阵乘法 (矩阵大小: %d x %d)...\n", size, size)
	
	// 创建并初始化矩阵
	a := matrix.InitializeMatrix(size)
	b := matrix.InitializeMatrix(size)
	
	// 测试标准矩阵乘法
	startTime := time.Now()
	_ = matrix.MatrixMultiply(a, b)
	standardTime := time.Since(startTime).Microseconds()
	fmt.Printf("标准矩阵乘法耗时: %.6f 秒\n", float64(standardTime)/1000000.0)
	
	// 测试分块矩阵乘法
	blockSize := 32 // 可调整块大小
	startTime = time.Now()
	_ = matrix.MatrixMultiplyBlocked(a, b, blockSize)
	blockedTime := time.Since(startTime).Microseconds()
	fmt.Printf("分块矩阵乘法耗时: %.6f 秒\n", float64(blockedTime)/1000000.0)
	
	return [2]int64{standardTime, blockedTime}
}

// AES加密测试
func testAES(size int) [2]int64 {
	fmt.Printf("测试AES加密 (数据大小: %d 字节)...\n", size)
	
	// 确保数据大小是AES块大小的倍数
	blockSize := 16 // AES块大小
	if size%blockSize != 0 {
		size = (size/blockSize + 1) * blockSize
	}
	
	// 生成随机数据
	data := crypto.GenerateRandomData(size)
	key := crypto.GenerateRandomData(16) // AES-128
	iv := crypto.GenerateRandomData(16)
	
	// 测试AES-CBC加密
	startTime := time.Now()
	encrypted, _ := crypto.AESEncrypt(data, key, iv)
	encryptTime := time.Since(startTime).Microseconds()
	fmt.Printf("AES-CBC加密耗时: %.6f 秒\n", float64(encryptTime)/1000000.0)
	
	// 测试AES-CBC解密
	startTime = time.Now()
	decrypted, _ := crypto.AESDecrypt(encrypted, key, iv)
	decryptTime := time.Since(startTime).Microseconds()
	fmt.Printf("AES-CBC解密耗时: %.6f 秒\n", float64(decryptTime)/1000000.0)
	
	// 验证解密结果
	correct := true
	for i := 0; i < len(data); i++ {
		if data[i] != decrypted[i] {
			correct = false
			break
		}
	}
	fmt.Printf("解密验证: %s\n", map[bool]string{true: "成功", false: "失败"}[correct])
	
	return [2]int64{encryptTime, decryptTime}
}

// Dijkstra算法测试
func testDijkstra(vertices, edges int) [2]int64 {
	fmt.Printf("测试Dijkstra算法 (顶点数: %d, 边数: %d)...\n", vertices, edges)
	
	// 创建图
	g := graph.NewGraph(vertices)
	
	// 随机添加边
	rand.Seed(time.Now().UnixNano())
	for i := 0; i < edges; i++ {
		src := rand.Intn(vertices)
		dest := rand.Intn(vertices)
		weight := 1 + rand.Intn(100) // 权重范围1-100
		
		if src != dest { // 避免自环
			g.AddEdge(src, dest, weight)
		}
	}
	
	// 选择源顶点
	src := 0
	
	// 测试标准Dijkstra算法
	startTime := time.Now()
	dist1, _ := g.Dijkstra(src)
	standardTime := time.Since(startTime).Microseconds()
	fmt.Printf("标准Dijkstra算法耗时: %.6f 秒\n", float64(standardTime)/1000000.0)
	
	// 测试优化的Dijkstra算法
	startTime = time.Now()
	dist2, _ := g.DijkstraOptimized(src)
	optimizedTime := time.Since(startTime).Microseconds()
	fmt.Printf("优化的Dijkstra算法耗时: %.6f 秒\n", float64(optimizedTime)/1000000.0)
	
	// 验证两种算法结果是否一致
	correct := true
	for i := 0; i < vertices; i++ {
		if dist1[i] != dist2[i] {
			correct = false
			break
		}
	}
	fmt.Printf("算法验证: %s\n", map[bool]string{true: "成功", false: "失败"}[correct])
	
	return [2]int64{standardTime, optimizedTime}
}

// 将结果写入文件
func writeResults(filename, arch, testName string, results [2]int64) {
	file, err := os.OpenFile(filename, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Printf("无法打开结果文件 %s: %v\n", filename, err)
		return
	}
	defer file.Close()
	
	// 写入结果
	line := fmt.Sprintf("%s,%s,%d,%d\n", arch, testName, results[0], results[1])
	if _, err := file.WriteString(line); err != nil {
		fmt.Printf("写入结果失败: %v\n", err)
	}
}

func main() {
	// 检查命令行参数
	if len(os.Args) < 2 {
		fmt.Printf("用法: %s <架构>\n", os.Args[0])
		fmt.Println("架构: x86_64, arm, riscv, loongarch")
		return
	}
	
	arch := os.Args[1]
	resultsFile := fmt.Sprintf("../../results/%s_results_go.csv", arch)
	
	// 创建或清空结果文件
	file, err := os.Create(resultsFile)
	if err != nil {
		fmt.Printf("无法创建结果文件 %s: %v\n", resultsFile, err)
		return
	}
	
	// 写入CSV头
	file.WriteString("架构,测试,结果1,结果2\n")
	file.Close()
	
	// 测试参数
	sortingSize := 100000
	matrixSize := 500
	aesSize := 1024 * 1024 // 1MB
	graphVertices := 1000
	graphEdges := 10000
	
	// 运行排序测试
	results := testSorting(sortingSize)
	writeResults(resultsFile, arch, "排序", results)
	
	// 运行矩阵乘法测试
	results = testMatrix(matrixSize)
	writeResults(resultsFile, arch, "矩阵", results)
	
	// 运行AES加密测试
	results = testAES(aesSize)
	writeResults(resultsFile, arch, "AES", results)
	
	// 运行Dijkstra算法测试
	results = testDijkstra(graphVertices, graphEdges)
	writeResults(resultsFile, arch, "Dijkstra", results)
	
	fmt.Printf("测试完成，结果已写入 %s\n", resultsFile)
}
