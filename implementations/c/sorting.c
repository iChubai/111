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

// 堆排序实现
void heapify(int arr[], int n, int i) {
    int largest = i;  // 初始化最大元素为根
    int left = 2 * i + 1;  // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点比根大
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点比当前最大的还大
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大元素不是根
    if (largest != i) {
        // 交换
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // 递归地堆化受影响的子树
        heapify(arr, n, largest);
    }
}

void heapsort(int arr[], int n) {
    // 构建堆
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 从堆中提取元素
    for (int i = n - 1; i > 0; i--) {
        // 将当前根移动到末尾
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // 对减小的堆调用堆化
        heapify(arr, i, 0);
    }
}

// Shell排序实现
void shellsort(int arr[], int n) {
    // 开始以较大的间隔，然后逐渐减小间隔
    for (int gap = n/2; gap > 0; gap /= 2) {
        // 对每个间隔进行插入排序
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// 基数排序的辅助函数
void countSort(int arr[], int n, int exp) {
    int output[n]; // 输出数组
    int count[10] = {0};

    // 统计出现次数
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // 改变count[i]，使其包含实际位置
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // 构建输出数组
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 将输出数组复制到arr[]
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// 获取数组中的最大值
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// 基数排序实现
void radixsort(int arr[], int n) {
    // 找出最大数以确定位数
    int max = getMax(arr, n);

    // 对每个位进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

// 计数排序实现
void countingsort(int arr[], int n, int max) {
    int* count = (int*)malloc((max + 1) * sizeof(int));
    int* output = (int*)malloc(n * sizeof(int));

    // 初始化计数数组
    for (int i = 0; i <= max; i++)
        count[i] = 0;

    // 统计每个元素出现的次数
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // 修改count[i]使其包含小于等于i的元素个数
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // 构建输出数组
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 将输出数组复制到arr[]
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    // 释放内存
    free(count);
    free(output);
}
