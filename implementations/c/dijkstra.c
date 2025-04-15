#include "../../algorithms/graph/dijkstra.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// 初始化图
void initialize_graph(Graph* graph, int vertices) {
    if (vertices > MAX_VERTICES) {
        printf("顶点数超过最大限制\n");
        return;
    }
    
    graph->vertices = vertices;
    
    // 初始化邻接矩阵
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjacency_matrix[i][j] = (i == j) ? 0 : INF;
        }
    }
}

// 添加边
void add_edge(Graph* graph, int src, int dest, int weight) {
    if (src >= 0 && src < graph->vertices && dest >= 0 && dest < graph->vertices) {
        graph->adjacency_matrix[src][dest] = weight;
    } else {
        printf("无效的顶点\n");
    }
}

// 查找距离最小的未访问顶点
int min_distance(int* dist, bool* visited, int vertices) {
    int min = INF, min_index = -1;
    
    for (int v = 0; v < vertices; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

// 标准Dijkstra算法实现
void dijkstra(Graph* graph, int src, int* dist, int* prev) {
    bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
    
    // 初始化
    for (int i = 0; i < graph->vertices; i++) {
        dist[i] = INF;
        prev[i] = -1;
        visited[i] = false;
    }
    
    // 源顶点到自身的距离为0
    dist[src] = 0;
    
    // 找到所有顶点的最短路径
    for (int count = 0; count < graph->vertices - 1; count++) {
        // 选择距离最小的未访问顶点
        int u = min_distance(dist, visited, graph->vertices);
        
        // 标记为已访问
        visited[u] = true;
        
        // 更新相邻顶点的距离
        for (int v = 0; v < graph->vertices; v++) {
            if (!visited[v] && 
                graph->adjacency_matrix[u][v] != INF && 
                dist[u] != INF && 
                dist[u] + graph->adjacency_matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjacency_matrix[u][v];
                prev[v] = u;
            }
        }
    }
    
    free(visited);
}

// 优先队列节点
typedef struct {
    int vertex;
    int distance;
} Node;

// 优先队列
typedef struct {
    Node* array;
    int capacity;
    int size;
} PriorityQueue;

// 创建优先队列
PriorityQueue* create_priority_queue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->array = (Node*)malloc(capacity * sizeof(Node));
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

// 交换节点
void swap_nodes(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// 上浮操作
void heapify_up(PriorityQueue* pq, int index) {
    int parent = (index - 1) / 2;
    
    if (index > 0 && pq->array[parent].distance > pq->array[index].distance) {
        swap_nodes(&pq->array[parent], &pq->array[index]);
        heapify_up(pq, parent);
    }
}

// 下沉操作
void heapify_down(PriorityQueue* pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < pq->size && pq->array[left].distance < pq->array[smallest].distance) {
        smallest = left;
    }
    
    if (right < pq->size && pq->array[right].distance < pq->array[smallest].distance) {
        smallest = right;
    }
    
    if (smallest != index) {
        swap_nodes(&pq->array[index], &pq->array[smallest]);
        heapify_down(pq, smallest);
    }
}

// 插入节点
void insert(PriorityQueue* pq, int vertex, int distance) {
    if (pq->size == pq->capacity) {
        printf("优先队列已满\n");
        return;
    }
    
    Node new_node = {vertex, distance};
    pq->array[pq->size] = new_node;
    pq->size++;
    
    heapify_up(pq, pq->size - 1);
}

// 提取最小节点
Node extract_min(PriorityQueue* pq) {
    if (pq->size <= 0) {
        Node empty = {-1, INF};
        return empty;
    }
    
    Node root = pq->array[0];
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;
    
    heapify_down(pq, 0);
    
    return root;
}

// 更新距离
void decrease_key(PriorityQueue* pq, int vertex, int distance) {
    for (int i = 0; i < pq->size; i++) {
        if (pq->array[i].vertex == vertex) {
            pq->array[i].distance = distance;
            heapify_up(pq, i);
            return;
        }
    }
}

// 检查顶点是否在优先队列中
bool is_in_queue(PriorityQueue* pq, int vertex) {
    for (int i = 0; i < pq->size; i++) {
        if (pq->array[i].vertex == vertex) {
            return true;
        }
    }
    return false;
}

// 优化版Dijkstra算法（使用优先队列）
void dijkstra_optimized(Graph* graph, int src, int* dist, int* prev) {
    PriorityQueue* pq = create_priority_queue(graph->vertices);
    
    // 初始化
    for (int i = 0; i < graph->vertices; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    
    // 源顶点到自身的距离为0
    dist[src] = 0;
    insert(pq, src, 0);
    
    while (pq->size > 0) {
        // 提取距离最小的顶点
        Node min_node = extract_min(pq);
        int u = min_node.vertex;
        
        // 更新相邻顶点的距离
        for (int v = 0; v < graph->vertices; v++) {
            if (graph->adjacency_matrix[u][v] != INF && 
                dist[u] != INF && 
                dist[u] + graph->adjacency_matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjacency_matrix[u][v];
                prev[v] = u;
                
                // 更新优先队列
                if (is_in_queue(pq, v)) {
                    decrease_key(pq, v, dist[v]);
                } else {
                    insert(pq, v, dist[v]);
                }
            }
        }
    }
    
    free(pq->array);
    free(pq);
}
