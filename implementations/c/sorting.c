#include "../../algorithms/sorting/sorting.h"
#include <stdlib.h>
#include <string.h>

// 快速排序实现
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // 交换元素
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    // 交换pivot元素
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return (i + 1);
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        // 获取分区点
        int pi = partition(arr, low, high);
        
        // 递归排序分区
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// 归并排序实现
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // 创建临时数组
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    // 复制数据到临时数组
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // 合并临时数组
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // 复制剩余元素
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // 释放临时数组
    free(L);
    free(R);
}

void mergesort(int arr[], int left, int right) {
    if (left < right) {
        // 计算中点
        int mid = left + (right - left) / 2;
        
        // 递归排序两半
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        
        // 合并已排序的两半
        merge(arr, left, mid, right);
    }
}
