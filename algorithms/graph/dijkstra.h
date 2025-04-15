#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stddef.h>
#include <limits.h>

// 图的最大顶点数
#define MAX_VERTICES 1000

// 表示无限大的距离
#define INF INT_MAX

// 图结构
typedef struct {
    int vertices;                    // 顶点数
    int adjacency_matrix[MAX_VERTICES][MAX_VERTICES]; // 邻接矩阵
} Graph;

// 函数声明
void initialize_graph(Graph* graph, int vertices);
void add_edge(Graph* graph, int src, int dest, int weight);
void dijkstra(Graph* graph, int src, int* dist, int* prev);

// 优化版本的Dijkstra算法（使用优先队列）
void dijkstra_optimized(Graph* graph, int src, int* dist, int* prev);

#endif // DIJKSTRA_H
