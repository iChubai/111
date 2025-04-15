#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../algorithms/sorting/sorting.h"

int main() {
    int size = 10;
    int* arr = (int*)malloc(size * sizeof(int));
    
    // 初始化随机数组
    srand(time(NULL));
    printf("原始数组: ");
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // 排序
    quicksort(arr, 0, size - 1);
    
    // 打印排序后的数组
    printf("排序后数组: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);
    return 0;
}
