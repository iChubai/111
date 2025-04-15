use std::collections::BinaryHeap;
use std::cmp::Ordering;
use priority_queue::PriorityQueue;

// 图结构
pub struct Graph {
    vertices: usize,
    adjacency_matrix: Vec<Vec<i32>>,
}

// 优先队列节点
#[derive(Copy, Clone, Eq, PartialEq)]
struct Node {
    vertex: usize,
    distance: i32,
}

// 为Node实现Ord和PartialOrd，使其可以用于优先队列
impl Ord for Node {
    fn cmp(&self, other: &Self) -> Ordering {
        // 注意：这里是最小堆，所以我们反转比较顺序
        other.distance.cmp(&self.distance)
    }
}

impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Graph {
    // 创建新图
    pub fn new(vertices: usize) -> Self {
        let mut adjacency_matrix = vec![vec![0; vertices]; vertices];
        
        // 初始化邻接矩阵
        for i in 0..vertices {
            for j in 0..vertices {
                adjacency_matrix[i][j] = if i == j { 0 } else { i32::MAX };
            }
        }
        
        Graph {
            vertices,
            adjacency_matrix,
        }
    }
    
    // 添加边
    pub fn add_edge(&mut self, src: usize, dest: usize, weight: i32) {
        if src < self.vertices && dest < self.vertices {
            self.adjacency_matrix[src][dest] = weight;
        }
    }
    
    // 标准Dijkstra算法
    pub fn dijkstra(&self, src: usize) -> (Vec<i32>, Vec<i32>) {
        let mut dist = vec![i32::MAX; self.vertices];
        let mut prev = vec![-1; self.vertices];
        let mut visited = vec![false; self.vertices];
        
        // 源顶点到自身的距离为0
        dist[src] = 0;
        
        // 找到所有顶点的最短路径
        for _ in 0..self.vertices {
            // 选择距离最小的未访问顶点
            let u = self.min_distance(&dist, &visited);
            
            // 如果没有可达的顶点，退出
            if u == usize::MAX {
                break;
            }
            
            // 标记为已访问
            visited[u] = true;
            
            // 更新相邻顶点的距离
            for v in 0..self.vertices {
                if !visited[v] && 
                   self.adjacency_matrix[u][v] != i32::MAX && 
                   dist[u] != i32::MAX && 
                   dist[u] + self.adjacency_matrix[u][v] < dist[v] {
                    dist[v] = dist[u] + self.adjacency_matrix[u][v];
                    prev[v] = u as i32;
                }
            }
        }
        
        (dist, prev)
    }
    
    // 查找距离最小的未访问顶点
    fn min_distance(&self, dist: &[i32], visited: &[bool]) -> usize {
        let mut min = i32::MAX;
        let mut min_index = usize::MAX;
        
        for v in 0..self.vertices {
            if !visited[v] && dist[v] < min {
                min = dist[v];
                min_index = v;
            }
        }
        
        min_index
    }
    
    // 优化的Dijkstra算法（使用优先队列）
    pub fn dijkstra_optimized(&self, src: usize) -> (Vec<i32>, Vec<i32>) {
        let mut dist = vec![i32::MAX; self.vertices];
        let mut prev = vec![-1; self.vertices];
        let mut pq = PriorityQueue::new();
        
        // 源顶点到自身的距离为0
        dist[src] = 0;
        pq.push(src, -0); // 使用负值作为优先级，因为PriorityQueue是最大堆
        
        while !pq.is_empty() {
            // 提取距离最小的顶点
            let (u, _) = pq.pop().unwrap();
            
            // 更新相邻顶点的距离
            for v in 0..self.vertices {
                if self.adjacency_matrix[u][v] != i32::MAX && 
                   dist[u] != i32::MAX && 
                   dist[u] + self.adjacency_matrix[u][v] < dist[v] {
                    dist[v] = dist[u] + self.adjacency_matrix[u][v];
                    prev[v] = u as i32;
                    
                    // 更新优先队列
                    pq.push(v, -dist[v]);
                }
            }
        }
        
        (dist, prev)
    }
}
