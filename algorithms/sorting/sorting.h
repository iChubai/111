#ifndef SORTING_H
#define SORTING_H

#include <stddef.h>

// 快速排序函数声明
void quicksort(int arr[], int low, int high);

// 归并排序函数声明
void mergesort(int arr[], int left, int right);

// 辅助函数
int partition(int arr[], int low, int high);
void merge(int arr[], int left, int mid, int right);

#endif // SORTING_H
