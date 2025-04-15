#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

// 矩阵乘法函数声明
void matrix_multiply(double** A, double** B, double** C, int n);

// 优化的矩阵乘法（使用分块技术）
void matrix_multiply_blocked(double** A, double** B, double** C, int n, int block_size);

// 辅助函数
double** allocate_matrix(int n);
void free_matrix(double** matrix, int n);
void initialize_matrix(double** matrix, int n);

#endif // MATRIX_H
