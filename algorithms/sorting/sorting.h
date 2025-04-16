#ifndef SORTING_H
#define SORTING_H

#include <stddef.h>

// 基本排序算法
void quicksort(int arr[], int low, int high);
void mergesort(int arr[], int left, int right);
void heapsort(int arr[], int n);
void shellsort(int arr[], int n);
void radixsort(int arr[], int n);
void countingsort(int arr[], int n, int max);

// 辅助函数
int partition(int arr[], int low, int high);
void merge(int arr[], int left, int mid, int right);
void heapify(int arr[], int n, int i);
int getMax(int arr[], int n);
void countSort(int arr[], int n, int exp);

#endif // SORTING_H
