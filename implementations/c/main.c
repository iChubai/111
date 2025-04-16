#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#include "../../algorithms/sorting/sorting.h"
#include "../../algorithms/matrix/matrix.h"
#include "../../algorithms/crypto/aes.h"
#include "../../algorithms/graph/dijkstra.h"

// 计时函数
double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

// 排序算法测试
void test_sorting(int size, int* results) {
    printf("测试排序算法 (数组大小: %d)...\n", size);

    // 生成随机数组
    int* arr1 = (int*)malloc(size * sizeof(int));
    int* arr2 = (int*)malloc(size * sizeof(int));
    int* arr3 = (int*)malloc(size * sizeof(int));
    int* arr4 = (int*)malloc(size * sizeof(int));
    int* arr5 = (int*)malloc(size * sizeof(int));
    int* arr6 = (int*)malloc(size * sizeof(int));
    int* sorted = (int*)malloc(size * sizeof(int)); // 用于验证排序结果

    // 初始化随机数组
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr1[i] = rand() % 10000;
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
        arr4[i] = arr1[i];
        arr5[i] = arr1[i];
        arr6[i] = arr1[i];
    }

    // 测试快速排序
    double start_time = get_time();
    quicksort(arr1, 0, size - 1);
    double end_time = get_time();
    double quicksort_time = end_time - start_time;
    printf("快速排序耗时: %.6f 秒\n", quicksort_time);
    results[0] = (int)(quicksort_time * 1000000); // 微秒

    // 保存排序结果供验证
    memcpy(sorted, arr1, size * sizeof(int));

    // 测试归并排序
    start_time = get_time();
    mergesort(arr2, 0, size - 1);
    end_time = get_time();
    double mergesort_time = end_time - start_time;
    printf("归并排序耗时: %.6f 秒\n", mergesort_time);
    results[1] = (int)(mergesort_time * 1000000); // 微秒

    // 验证归并排序结果
    int mergesort_correct = 1;
    for (int i = 0; i < size; i++) {
        if (arr2[i] != sorted[i]) {
            mergesort_correct = 0;
            break;
        }
    }
    printf("归并排序验证: %s\n", mergesort_correct ? "成功" : "失败");

    // 测试堆排序
    start_time = get_time();
    heapsort(arr3, size);
    end_time = get_time();
    double heapsort_time = end_time - start_time;
    printf("堆排序耗时: %.6f 秒\n", heapsort_time);
    results[2] = (int)(heapsort_time * 1000000); // 微秒

    // 验证堆排序结果
    int heapsort_correct = 1;
    for (int i = 0; i < size; i++) {
        if (arr3[i] != sorted[i]) {
            heapsort_correct = 0;
            break;
        }
    }
    printf("堆排序验证: %s\n", heapsort_correct ? "成功" : "失败");

    // 测试Shell排序
    start_time = get_time();
    shellsort(arr4, size);
    end_time = get_time();
    double shellsort_time = end_time - start_time;
    printf("Shell排序耗时: %.6f 秒\n", shellsort_time);
    results[3] = (int)(shellsort_time * 1000000); // 微秒

    // 验证Shell排序结果
    int shellsort_correct = 1;
    for (int i = 0; i < size; i++) {
        if (arr4[i] != sorted[i]) {
            shellsort_correct = 0;
            break;
        }
    }
    printf("Shell排序验证: %s\n", shellsort_correct ? "成功" : "失败");

    // 测试基数排序
    start_time = get_time();
    radixsort(arr5, size);
    end_time = get_time();
    double radixsort_time = end_time - start_time;
    printf("基数排序耗时: %.6f 秒\n", radixsort_time);
    results[4] = (int)(radixsort_time * 1000000); // 微秒

    // 验证基数排序结果
    int radixsort_correct = 1;
    for (int i = 0; i < size; i++) {
        if (arr5[i] != sorted[i]) {
            radixsort_correct = 0;
            break;
        }
    }
    printf("基数排序验证: %s\n", radixsort_correct ? "成功" : "失败");

    // 测试计数排序
    start_time = get_time();
    countingsort(arr6, size, 10000);
    end_time = get_time();
    double countingsort_time = end_time - start_time;
    printf("计数排序耗时: %.6f 秒\n", countingsort_time);
    results[5] = (int)(countingsort_time * 1000000); // 微秒

    // 验证计数排序结果
    int countingsort_correct = 1;
    for (int i = 0; i < size; i++) {
        if (arr6[i] != sorted[i]) {
            countingsort_correct = 0;
            break;
        }
    }
    printf("计数排序验证: %s\n", countingsort_correct ? "成功" : "失败");

    // 释放内存
    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
    free(arr5);
    free(arr6);
    free(sorted);
}

// 矩阵运算测试
void test_matrix(int size, int* results) {
    printf("测试矩阵运算 (矩阵大小: %d x %d)...\n", size, size);

    // 分配矩阵内存
    double** A = allocate_matrix(size);
    double** B = allocate_matrix(size);
    double** C = allocate_matrix(size);
    double** D = allocate_matrix(size);
    double** E = allocate_matrix(size);
    double** F = allocate_matrix(size);
    double** G = allocate_matrix(size);

    // 初始化矩阵
    initialize_matrix(A, size);
    initialize_matrix(B, size);

    // 测试标准矩阵乘法
    double start_time = get_time();
    matrix_multiply(A, B, C, size);
    double end_time = get_time();
    double standard_time = end_time - start_time;
    printf("标准矩阵乘法耗时: %.6f 秒\n", standard_time);
    results[0] = (int)(standard_time * 1000000); // 微秒

    // 测试分块矩阵乘法
    int block_size = 32; // 可调整块大小
    start_time = get_time();
    matrix_multiply_blocked(A, B, D, size, block_size);
    end_time = get_time();
    double blocked_time = end_time - start_time;
    printf("分块矩阵乘法耗时: %.6f 秒\n", blocked_time);
    results[1] = (int)(blocked_time * 1000000); // 微秒

    // 验证分块矩阵乘法结果
    int blocked_correct = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fabs(C[i][j] - D[i][j]) > 1e-10) {
                blocked_correct = 0;
                break;
            }
        }
        if (!blocked_correct) break;
    }
    printf("分块矩阵乘法验证: %s\n", blocked_correct ? "成功" : "失败");

    // 测试Strassen矩阵乘法
    start_time = get_time();
    matrix_multiply_strassen(A, B, E, size);
    end_time = get_time();
    double strassen_time = end_time - start_time;
    printf("Strassen矩阵乘法耗时: %.6f 秒\n", strassen_time);
    results[2] = (int)(strassen_time * 1000000); // 微秒

    // 验证Strassen矩阵乘法结果
    int strassen_correct = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fabs(C[i][j] - E[i][j]) > 1e-10) {
                strassen_correct = 0;
                break;
            }
        }
        if (!strassen_correct) break;
    }
    printf("Strassen矩阵乘法验证: %s\n", strassen_correct ? "成功" : "失败");

    // 测试矩阵转置
    start_time = get_time();
    matrix_transpose(A, F, size);
    end_time = get_time();
    double transpose_time = end_time - start_time;
    printf("矩阵转置耗时: %.6f 秒\n", transpose_time);
    results[3] = (int)(transpose_time * 1000000); // 微秒

    // 测试LU分解
    start_time = get_time();
    matrix_lu_decomposition(A, F, G, size);
    end_time = get_time();
    double lu_time = end_time - start_time;
    printf("LU分解耗时: %.6f 秒\n", lu_time);
    results[4] = (int)(lu_time * 1000000); // 微秒

    // 测试矩阵求逆
    // 使用较小的矩阵来测试求逆，因为大矩阵可能会奇异
    int inv_size = size > 100 ? 100 : size;
    double** small_A = allocate_matrix(inv_size);
    double** small_Ainv = allocate_matrix(inv_size);
    initialize_matrix(small_A, inv_size);

    start_time = get_time();
    matrix_inverse(small_A, small_Ainv, inv_size);
    end_time = get_time();
    double inverse_time = end_time - start_time;
    printf("矩阵求逆耗时: %.6f 秒\n", inverse_time);
    results[5] = (int)(inverse_time * 1000000); // 微秒

    // 释放矩阵内存
    free_matrix(A, size);
    free_matrix(B, size);
    free_matrix(C, size);
    free_matrix(D, size);
    free_matrix(E, size);
    free_matrix(F, size);
    free_matrix(G, size);
    free_matrix(small_A, inv_size);
    free_matrix(small_Ainv, inv_size);
}

// AES加密测试
void test_aes(int size, int* results) {
    printf("测试AES加密 (数据大小: %d 字节)...\n", size);

    // 确保数据大小是AES块大小的倍数
    if (size % AES_BLOCK_SIZE != 0) {
        size = (size / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
    }

    // 分配内存
    uint8_t* data = (uint8_t*)malloc(size);
    uint8_t* encrypted = (uint8_t*)malloc(size);
    uint8_t* decrypted = (uint8_t*)malloc(size);
    uint8_t key[AES_128_KEY_SIZE];
    uint8_t iv[AES_BLOCK_SIZE];

    // 初始化随机数据、密钥和IV
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        data[i] = rand() % 256;
    }
    for (int i = 0; i < AES_128_KEY_SIZE; i++) {
        key[i] = rand() % 256;
    }
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        iv[i] = rand() % 256;
    }

    // 复制数据用于加密
    memcpy(encrypted, data, size);

    // 初始化AES上下文
    AES_ctx ctx;
    AES_init_ctx(&ctx, key, AES_128_KEY_SIZE);

    // 测试AES-CBC加密
    double start_time = get_time();
    AES_CBC_encrypt(&ctx, iv, encrypted, size);
    double end_time = get_time();
    double encrypt_time = end_time - start_time;
    printf("AES-CBC加密耗时: %.6f 秒\n", encrypt_time);
    results[0] = (int)(encrypt_time * 1000000); // 微秒

    // 复制IV（因为它在加密过程中被修改）
    uint8_t iv_copy[AES_BLOCK_SIZE];
    memcpy(iv_copy, iv, AES_BLOCK_SIZE);

    // 复制加密数据用于解密
    memcpy(decrypted, encrypted, size);

    // 测试AES-CBC解密
    start_time = get_time();
    AES_CBC_decrypt(&ctx, iv_copy, decrypted, size);
    end_time = get_time();
    double decrypt_time = end_time - start_time;
    printf("AES-CBC解密耗时: %.6f 秒\n", decrypt_time);
    results[1] = (int)(decrypt_time * 1000000); // 微秒

    // 验证解密结果
    int correct = 1;
    for (int i = 0; i < size; i++) {
        if (data[i] != decrypted[i]) {
            correct = 0;
            break;
        }
    }
    printf("解密验证: %s\n", correct ? "成功" : "失败");

    // 释放内存
    free(data);
    free(encrypted);
    free(decrypted);
}

// Dijkstra算法测试
void test_dijkstra(int vertices, int edges, int* results) {
    printf("测试Dijkstra算法 (顶点数: %d, 边数: %d)...\n", vertices, edges);

    // 创建图
    Graph graph;
    initialize_graph(&graph, vertices);

    // 随机添加边
    srand(time(NULL));
    for (int i = 0; i < edges; i++) {
        int src = rand() % vertices;
        int dest = rand() % vertices;
        int weight = 1 + rand() % 100; // 权重范围1-100

        if (src != dest) { // 避免自环
            add_edge(&graph, src, dest, weight);
        }
    }

    // 分配距离和前驱数组
    int* dist1 = (int*)malloc(vertices * sizeof(int));
    int* prev1 = (int*)malloc(vertices * sizeof(int));
    int* dist2 = (int*)malloc(vertices * sizeof(int));
    int* prev2 = (int*)malloc(vertices * sizeof(int));

    // 选择源顶点
    int src = 0;

    // 测试标准Dijkstra算法
    double start_time = get_time();
    dijkstra(&graph, src, dist1, prev1);
    double end_time = get_time();
    double standard_time = end_time - start_time;
    printf("标准Dijkstra算法耗时: %.6f 秒\n", standard_time);
    results[0] = (int)(standard_time * 1000000); // 微秒

    // 测试优化的Dijkstra算法
    start_time = get_time();
    dijkstra_optimized(&graph, src, dist2, prev2);
    end_time = get_time();
    double optimized_time = end_time - start_time;
    printf("优化的Dijkstra算法耗时: %.6f 秒\n", optimized_time);
    results[1] = (int)(optimized_time * 1000000); // 微秒

    // 验证两种算法结果是否一致
    int correct = 1;
    for (int i = 0; i < vertices; i++) {
        if (dist1[i] != dist2[i]) {
            correct = 0;
            break;
        }
    }
    printf("算法验证: %s\n", correct ? "成功" : "失败");

    // 释放内存
    free(dist1);
    free(prev1);
    free(dist2);
    free(prev2);
}

// 将结果写入文件
void write_results(const char* filename, const char* arch, const char* test_name, int* results, int num_results) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    // 写入结果
    fprintf(file, "%s,%s", arch, test_name);
    for (int i = 0; i < num_results; i++) {
        fprintf(file, ",%d", results[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}

int main(int argc, char* argv[]) {
    // 检查命令行参数
    if (argc < 2) {
        printf("用法: %s <架构>\n", argv[0]);
        printf("架构: x86_64, arm, riscv, loongarch\n");
        return 1;
    }

    const char* arch = argv[1];
    char results_file[256];
    sprintf(results_file, "../../results/%s_results.csv", arch);

    // 创建或清空结果文件
    FILE* file = fopen(results_file, "w");
    if (file == NULL) {
        printf("无法创建结果文件 %s\n", results_file);
        return 1;
    }

    // 写入CSV头
    fprintf(file, "架构,测试类型,算法1,算法2,算法3,算法4,算法5,算法6\n");

    // 写入排序算法列名
    fprintf(file, "架构,排序,快速排序,归并排序,堆排序,Shell排序,基数排序,计数排序\n");

    // 写入矩阵算法列名
    fprintf(file, "架构,矩阵,标准乘法,分块乘法,Strassen乘法,矩阵转置,LU分解,矩阵求逆\n");

    // 写入AES算法列名
    fprintf(file, "架构,AES,加密,解密,,,,\n");

    // 写入Dijkstra算法列名
    fprintf(file, "架构,Dijkstra,标准算法,优化算法,,,,\n");

    fclose(file);

    // 测试参数
    int sorting_size = 100000;
    int matrix_size = 500;
    int aes_size = 1024 * 1024; // 1MB
    int graph_vertices = 1000;
    int graph_edges = 10000;

    // 结果数组
    int sorting_results[6];
    int matrix_results[6];
    int other_results[2];

    // 运行排序测试
    test_sorting(sorting_size, sorting_results);
    write_results(results_file, arch, "排序", sorting_results, 6);

    // 运行矩阵运算测试
    test_matrix(matrix_size, matrix_results);
    write_results(results_file, arch, "矩阵", matrix_results, 6);

    // 运行AES加密测试
    test_aes(aes_size, other_results);
    write_results(results_file, arch, "AES", other_results, 2);

    // 运行Dijkstra算法测试
    test_dijkstra(graph_vertices, graph_edges, other_results);
    write_results(results_file, arch, "Dijkstra", other_results, 2);

    printf("测试完成，结果已写入 %s\n", results_file);

    return 0;
}
