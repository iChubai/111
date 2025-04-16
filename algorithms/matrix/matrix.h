#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

// 基本矩阵运算
void matrix_multiply(double** A, double** B, double** C, int n);                      // 标准矩阵乘法
void matrix_multiply_blocked(double** A, double** B, double** C, int n, int block_size); // 分块矩阵乘法
void matrix_multiply_strassen(double** A, double** B, double** C, int n);             // Strassen矩阵乘法
void matrix_transpose(double** A, double** B, int n);                                 // 矩阵转置
void matrix_add(double** A, double** B, double** C, int n);                           // 矩阵加法
void matrix_subtract(double** A, double** B, double** C, int n);                      // 矩阵减法

// 高级矩阵运算
void matrix_lu_decomposition(double** A, double** L, double** U, int n);              // LU分解
void matrix_inverse(double** A, double** Ainv, int n);                                // 矩阵求逆
void matrix_determinant(double** A, double* det, int n);                              // 求行列式

// 辅助函数
double** allocate_matrix(int n);
void free_matrix(double** matrix, int n);
void initialize_matrix(double** matrix, int n);
void copy_matrix(double** src, double** dst, int n);
void print_matrix(double** A, int n);

#endif // MATRIX_H
