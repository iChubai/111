use rand::Rng;

// 初始化矩阵
pub fn initialize_matrix(n: usize) -> Vec<Vec<f64>> {
    let mut rng = rand::thread_rng();
    let mut matrix = vec![vec![0.0; n]; n];
    
    for i in 0..n {
        for j in 0..n {
            matrix[i][j] = rng.gen::<f64>();
        }
    }
    
    matrix
}

// 标准矩阵乘法
pub fn matrix_multiply(a: &Vec<Vec<f64>>, b: &Vec<Vec<f64>>) -> Vec<Vec<f64>> {
    let n = a.len();
    let mut c = vec![vec![0.0; n]; n];
    
    for i in 0..n {
        for j in 0..n {
            for k in 0..n {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    c
}

// 分块矩阵乘法
pub fn matrix_multiply_blocked(a: &Vec<Vec<f64>>, b: &Vec<Vec<f64>>, block_size: usize) -> Vec<Vec<f64>> {
    let n = a.len();
    let mut c = vec![vec![0.0; n]; n];
    
    // 分块矩阵乘法
    for i in (0..n).step_by(block_size) {
        for j in (0..n).step_by(block_size) {
            for k in (0..n).step_by(block_size) {
                // 处理当前块
                for ii in i..std::cmp::min(i + block_size, n) {
                    for jj in j..std::cmp::min(j + block_size, n) {
                        for kk in k..std::cmp::min(k + block_size, n) {
                            c[ii][jj] += a[ii][kk] * b[kk][jj];
                        }
                    }
                }
            }
        }
    }
    
    c
}
