package graph

import (
	"container/heap"
	"math"
)

// 图结构
type Graph struct {
	vertices        int
	adjacencyMatrix [][]int
}

// 创建新图
func NewGraph(vertices int) *Graph {
	adjacencyMatrix := make([][]int, vertices)
	
	// 初始化邻接矩阵
	for i := 0; i < vertices; i++ {
		adjacencyMatrix[i] = make([]int, vertices)
		for j := 0; j < vertices; j++ {
			if i == j {
				adjacencyMatrix[i][j] = 0
			} else {
				adjacencyMatrix[i][j] = math.MaxInt32
			}
		}
	}
	
	return &Graph{
		vertices:        vertices,
		adjacencyMatrix: adjacencyMatrix,
	}
}

// 添加边
func (g *Graph) AddEdge(src, dest, weight int) {
	if src >= 0 && src < g.vertices && dest >= 0 && dest < g.vertices {
		g.adjacencyMatrix[src][dest] = weight
	}
}

// 标准Dijkstra算法
func (g *Graph) Dijkstra(src int) ([]int, []int) {
	dist := make([]int, g.vertices)
	prev := make([]int, g.vertices)
	visited := make([]bool, g.vertices)
	
	// 初始化
	for i := 0; i < g.vertices; i++ {
		dist[i] = math.MaxInt32
		prev[i] = -1
		visited[i] = false
	}
	
	// 源顶点到自身的距离为0
	dist[src] = 0
	
	// 找到所有顶点的最短路径
	for count := 0; count < g.vertices-1; count++ {
		// 选择距离最小的未访问顶点
		u := g.minDistance(dist, visited)
		
		// 如果没有可达的顶点，退出
		if u == -1 {
			break
		}
		
		// 标记为已访问
		visited[u] = true
		
		// 更新相邻顶点的距离
		for v := 0; v < g.vertices; v++ {
			if !visited[v] &&
				g.adjacencyMatrix[u][v] != math.MaxInt32 &&
				dist[u] != math.MaxInt32 &&
				dist[u]+g.adjacencyMatrix[u][v] < dist[v] {
				dist[v] = dist[u] + g.adjacencyMatrix[u][v]
				prev[v] = u
			}
		}
	}
	
	return dist, prev
}

// 查找距离最小的未访问顶点
func (g *Graph) minDistance(dist []int, visited []bool) int {
	min := math.MaxInt32
	minIndex := -1
	
	for v := 0; v < g.vertices; v++ {
		if !visited[v] && dist[v] < min {
			min = dist[v]
			minIndex = v
		}
	}
	
	return minIndex
}

// 优先队列节点
type Node struct {
	vertex   int
	distance int
	index    int // 堆中的索引
}

// 优先队列
type PriorityQueue []*Node

func (pq PriorityQueue) Len() int { return len(pq) }

func (pq PriorityQueue) Less(i, j int) bool {
	return pq[i].distance < pq[j].distance
}

func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
	pq[i].index = i
	pq[j].index = j
}

func (pq *PriorityQueue) Push(x interface{}) {
	n := len(*pq)
	node := x.(*Node)
	node.index = n
	*pq = append(*pq, node)
}

func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	node := old[n-1]
	old[n-1] = nil  // 避免内存泄漏
	node.index = -1 // 标记为已移除
	*pq = old[0 : n-1]
	return node
}

// 优化的Dijkstra算法（使用优先队列）
func (g *Graph) DijkstraOptimized(src int) ([]int, []int) {
	dist := make([]int, g.vertices)
	prev := make([]int, g.vertices)
	
	// 初始化
	for i := 0; i < g.vertices; i++ {
		dist[i] = math.MaxInt32
		prev[i] = -1
	}
	
	// 源顶点到自身的距离为0
	dist[src] = 0
	
	// 创建优先队列
	pq := make(PriorityQueue, 0)
	heap.Init(&pq)
	
	// 将源顶点加入队列
	heap.Push(&pq, &Node{
		vertex:   src,
		distance: 0,
	})
	
	// 处理队列
	for pq.Len() > 0 {
		// 提取距离最小的顶点
		u := heap.Pop(&pq).(*Node).vertex
		
		// 更新相邻顶点的距离
		for v := 0; v < g.vertices; v++ {
			if g.adjacencyMatrix[u][v] != math.MaxInt32 &&
				dist[u] != math.MaxInt32 &&
				dist[u]+g.adjacencyMatrix[u][v] < dist[v] {
				dist[v] = dist[u] + g.adjacencyMatrix[u][v]
				prev[v] = u
				
				// 将更新的顶点加入队列
				heap.Push(&pq, &Node{
					vertex:   v,
					distance: dist[v],
				})
			}
		}
	}
	
	return dist, prev
}
