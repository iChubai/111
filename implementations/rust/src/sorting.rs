// 快速排序实现
pub fn quicksort(arr: &mut [i32], low: isize, high: isize) {
    if low < high {
        let pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

fn partition(arr: &mut [i32], low: isize, high: isize) -> isize {
    let pivot = arr[high as usize];
    let mut i = low - 1;
    
    for j in low..high {
        if arr[j as usize] < pivot {
            i += 1;
            arr.swap(i as usize, j as usize);
        }
    }
    
    arr.swap((i + 1) as usize, high as usize);
    i + 1
}

// 归并排序实现
pub fn mergesort(arr: &mut [i32], left: isize, right: isize) {
    if left < right {
        let mid = left + (right - left) / 2;
        
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

fn merge(arr: &mut [i32], left: isize, mid: isize, right: isize) {
    let n1 = mid - left + 1;
    let n2 = right - mid;
    
    // 创建临时数组
    let mut l = vec![0; n1 as usize];
    let mut r = vec![0; n2 as usize];
    
    // 复制数据到临时数组
    for i in 0..n1 {
        l[i as usize] = arr[(left + i) as usize];
    }
    for j in 0..n2 {
        r[j as usize] = arr[(mid + 1 + j) as usize];
    }
    
    // 合并临时数组
    let mut i = 0;
    let mut j = 0;
    let mut k = left;
    
    while i < n1 && j < n2 {
        if l[i as usize] <= r[j as usize] {
            arr[k as usize] = l[i as usize];
            i += 1;
        } else {
            arr[k as usize] = r[j as usize];
            j += 1;
        }
        k += 1;
    }
    
    // 复制剩余元素
    while i < n1 {
        arr[k as usize] = l[i as usize];
        i += 1;
        k += 1;
    }
    
    while j < n2 {
        arr[k as usize] = r[j as usize];
        j += 1;
        k += 1;
    }
}
