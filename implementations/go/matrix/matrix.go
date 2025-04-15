package matrix

import (
	"math/rand"
	"time"
)

// 初始化矩阵
func InitializeMatrix(n int) [][]float64 {
	rand.Seed(time.Now().UnixNano())
	matrix := make([][]float64, n)
	
	for i := 0; i < n; i++ {
		matrix[i] = make([]float64, n)
		for j := 0; j < n; j++ {
			matrix[i][j] = rand.Float64()
		}
	}
	
	return matrix
}

// 标准矩阵乘法
func MatrixMultiply(a, b [][]float64) [][]float64 {
	n := len(a)
	c := make([][]float64, n)
	
	for i := 0; i < n; i++ {
		c[i] = make([]float64, n)
		for j := 0; j < n; j++ {
			for k := 0; k < n; k++ {
				c[i][j] += a[i][k] * b[k][j]
			}
		}
	}
	
	return c
}

// 分块矩阵乘法
func MatrixMultiplyBlocked(a, b [][]float64, blockSize int) [][]float64 {
	n := len(a)
	c := make([][]float64, n)
	
	for i := 0; i < n; i++ {
		c[i] = make([]float64, n)
	}
	
	// 分块矩阵乘法
	for i := 0; i < n; i += blockSize {
		for j := 0; j < n; j += blockSize {
			for k := 0; k < n; k += blockSize {
				// 处理当前块
				for ii := i; ii < min(i+blockSize, n); ii++ {
					for jj := j; jj < min(j+blockSize, n); jj++ {
						for kk := k; kk < min(k+blockSize, n); kk++ {
							c[ii][jj] += a[ii][kk] * b[kk][jj]
						}
					}
				}
			}
		}
	}
	
	return c
}

// 辅助函数：返回两个整数中的较小值
func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
