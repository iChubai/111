#include "../../algorithms/matrix/matrix.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// 分配矩阵内存
double** allocate_matrix(int n) {
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

// 释放矩阵内存
void free_matrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// 初始化矩阵
void initialize_matrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

// 复制矩阵
void copy_matrix(double** src, double** dst, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

// 打印矩阵
void print_matrix(double** A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.4f ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 标准矩阵乘法实现
void matrix_multiply(double** A, double** B, double** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// 分块矩阵乘法实现（优化缓存使用）
void matrix_multiply_blocked(double** A, double** B, double** C, int n, int block_size) {
    // 初始化结果矩阵为0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
        }
    }

    // 分块矩阵乘法
    for (int i = 0; i < n; i += block_size) {
        for (int j = 0; j < n; j += block_size) {
            for (int k = 0; k < n; k += block_size) {
                // 处理当前块
                for (int ii = i; ii < i + block_size && ii < n; ii++) {
                    for (int jj = j; jj < j + block_size && jj < n; jj++) {
                        for (int kk = k; kk < k + block_size && kk < n; kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

// 矩阵加法
void matrix_add(double** A, double** B, double** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// 矩阵减法
void matrix_subtract(double** A, double** B, double** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// 矩阵转置
void matrix_transpose(double** A, double** B, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B[j][i] = A[i][j];
        }
    }
}

// Strassen矩阵乘法的递归实现
void strassen_recursive(double** A, double** B, double** C, int n) {
    // 基本情况：当矩阵足够小时使用标准乘法
    if (n <= 64) {
        matrix_multiply(A, B, C, n);
        return;
    }

    int m = n / 2;

    // 分配子矩阵内存
    double** A11 = allocate_matrix(m);
    double** A12 = allocate_matrix(m);
    double** A21 = allocate_matrix(m);
    double** A22 = allocate_matrix(m);

    double** B11 = allocate_matrix(m);
    double** B12 = allocate_matrix(m);
    double** B21 = allocate_matrix(m);
    double** B22 = allocate_matrix(m);

    double** C11 = allocate_matrix(m);
    double** C12 = allocate_matrix(m);
    double** C21 = allocate_matrix(m);
    double** C22 = allocate_matrix(m);

    double** M1 = allocate_matrix(m);
    double** M2 = allocate_matrix(m);
    double** M3 = allocate_matrix(m);
    double** M4 = allocate_matrix(m);
    double** M5 = allocate_matrix(m);
    double** M6 = allocate_matrix(m);
    double** M7 = allocate_matrix(m);

    double** temp1 = allocate_matrix(m);
    double** temp2 = allocate_matrix(m);

    // 将原矩阵分割为四个子矩阵
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];
            B22[i][j] = B[i + m][j + m];
        }
    }

    // 计算M1 = (A11 + A22) * (B11 + B22)
    matrix_add(A11, A22, temp1, m);
    matrix_add(B11, B22, temp2, m);
    strassen_recursive(temp1, temp2, M1, m);

    // 计算M2 = (A21 + A22) * B11
    matrix_add(A21, A22, temp1, m);
    strassen_recursive(temp1, B11, M2, m);

    // 计算M3 = A11 * (B12 - B22)
    matrix_subtract(B12, B22, temp1, m);
    strassen_recursive(A11, temp1, M3, m);

    // 计算M4 = A22 * (B21 - B11)
    matrix_subtract(B21, B11, temp1, m);
    strassen_recursive(A22, temp1, M4, m);

    // 计算M5 = (A11 + A12) * B22
    matrix_add(A11, A12, temp1, m);
    strassen_recursive(temp1, B22, M5, m);

    // 计算M6 = (A21 - A11) * (B11 + B12)
    matrix_subtract(A21, A11, temp1, m);
    matrix_add(B11, B12, temp2, m);
    strassen_recursive(temp1, temp2, M6, m);

    // 计算M7 = (A12 - A22) * (B21 + B22)
    matrix_subtract(A12, A22, temp1, m);
    matrix_add(B21, B22, temp2, m);
    strassen_recursive(temp1, temp2, M7, m);

    // 计算C的子矩阵
    // C11 = M1 + M4 - M5 + M7
    matrix_add(M1, M4, temp1, m);
    matrix_subtract(temp1, M5, temp2, m);
    matrix_add(temp2, M7, C11, m);

    // C12 = M3 + M5
    matrix_add(M3, M5, C12, m);

    // C21 = M2 + M4
    matrix_add(M2, M4, C21, m);

    // C22 = M1 - M2 + M3 + M6
    matrix_subtract(M1, M2, temp1, m);
    matrix_add(temp1, M3, temp2, m);
    matrix_add(temp2, M6, C22, m);

    // 将结果复制回原矩阵C
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = C11[i][j];
            C[i][j + m] = C12[i][j];
            C[i + m][j] = C21[i][j];
            C[i + m][j + m] = C22[i][j];
        }
    }

    // 释放内存
    free_matrix(A11, m);
    free_matrix(A12, m);
    free_matrix(A21, m);
    free_matrix(A22, m);

    free_matrix(B11, m);
    free_matrix(B12, m);
    free_matrix(B21, m);
    free_matrix(B22, m);

    free_matrix(C11, m);
    free_matrix(C12, m);
    free_matrix(C21, m);
    free_matrix(C22, m);

    free_matrix(M1, m);
    free_matrix(M2, m);
    free_matrix(M3, m);
    free_matrix(M4, m);
    free_matrix(M5, m);
    free_matrix(M6, m);
    free_matrix(M7, m);

    free_matrix(temp1, m);
    free_matrix(temp2, m);
}

// Strassen矩阵乘法入口函数
void matrix_multiply_strassen(double** A, double** B, double** C, int n) {
    // 确保矩阵大小是2的幂
    int power_of_two = 1;
    while (power_of_two < n) {
        power_of_two *= 2;
    }

    if (power_of_two == n) {
        // 如果已经是2的幂，直接调用
        strassen_recursive(A, B, C, n);
    } else {
        // 如果不是2的幂，需要填充
        double** A_padded = allocate_matrix(power_of_two);
        double** B_padded = allocate_matrix(power_of_two);
        double** C_padded = allocate_matrix(power_of_two);

        // 初始化为0
        for (int i = 0; i < power_of_two; i++) {
            for (int j = 0; j < power_of_two; j++) {
                A_padded[i][j] = 0.0;
                B_padded[i][j] = 0.0;
            }
        }

        // 复制原始数据
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A_padded[i][j] = A[i][j];
                B_padded[i][j] = B[i][j];
            }
        }

        // 调用Strassen算法
        strassen_recursive(A_padded, B_padded, C_padded, power_of_two);

        // 复制结果
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = C_padded[i][j];
            }
        }

        // 释放内存
        free_matrix(A_padded, power_of_two);
        free_matrix(B_padded, power_of_two);
        free_matrix(C_padded, power_of_two);
    }
}

// LU分解
void matrix_lu_decomposition(double** A, double** L, double** U, int n) {
    // 初始化L为单位矩阵，U为零矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                L[i][j] = 1.0;
            } else {
                L[i][j] = 0.0;
            }
            U[i][j] = 0.0;
        }
    }

    // 计算LU分解
    for (int i = 0; i < n; i++) {
        // 计算U的第 i 行
        for (int j = i; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++) {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - sum;
        }

        // 计算L的第 i 列
        for (int j = i + 1; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++) {
                sum += L[j][k] * U[k][i];
            }
            if (U[i][i] == 0) {
                // 避免除零
                L[j][i] = 0;
            } else {
                L[j][i] = (A[j][i] - sum) / U[i][i];
            }
        }
    }
}

// 求矩阵行列式
void matrix_determinant(double** A, double* det, int n) {
    if (n == 1) {
        *det = A[0][0];
        return;
    }

    if (n == 2) {
        *det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
        return;
    }

    // 使用LU分解求行列式
    double** L = allocate_matrix(n);
    double** U = allocate_matrix(n);

    matrix_lu_decomposition(A, L, U, n);

    // 行列式等于U对角线元素的乘积
    *det = 1.0;
    for (int i = 0; i < n; i++) {
        *det *= U[i][i];
    }

    free_matrix(L, n);
    free_matrix(U, n);
}

// 求矩阵的逆
void matrix_inverse(double** A, double** Ainv, int n) {
    // 创建增广矩阵 [A|I]
    double** augmented = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        augmented[i] = (double*)malloc(2 * n * sizeof(double));
    }

    // 初始化增广矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = A[i][j];
        }
        for (int j = n; j < 2 * n; j++) {
            augmented[i][j] = (i == (j - n)) ? 1.0 : 0.0;
        }
    }

    // 高斯消元
    for (int i = 0; i < n; i++) {
        // 寻找主元
        double max_val = fabs(augmented[i][i]);
        int max_row = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(augmented[j][i]) > max_val) {
                max_val = fabs(augmented[j][i]);
                max_row = j;
            }
        }

        // 交换行
        if (max_row != i) {
            for (int j = 0; j < 2 * n; j++) {
                double temp = augmented[i][j];
                augmented[i][j] = augmented[max_row][j];
                augmented[max_row][j] = temp;
            }
        }

        // 将主元归一化
        double pivot = augmented[i][i];
        if (pivot == 0) {
            // 矩阵奇异，无法求逆
            printf("Matrix is singular, cannot compute inverse\n");
            for (int i = 0; i < n; i++) {
                free(augmented[i]);
            }
            free(augmented);
            return;
        }

        for (int j = 0; j < 2 * n; j++) {
            augmented[i][j] /= pivot;
        }

        // 消元
        for (int j = 0; j < n; j++) {
            if (j != i) {
                double factor = augmented[j][i];
                for (int k = 0; k < 2 * n; k++) {
                    augmented[j][k] -= factor * augmented[i][k];
                }
            }
        }
    }

    // 提取逆矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Ainv[i][j] = augmented[i][j + n];
        }
    }

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(augmented[i]);
    }
    free(augmented);
}
