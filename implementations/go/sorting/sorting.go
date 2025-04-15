package sorting

// 快速排序实现
func Quicksort(arr []int, low, high int) {
	if low < high {
		pi := partition(arr, low, high)
		Quicksort(arr, low, pi-1)
		Quicksort(arr, pi+1, high)
	}
}

func partition(arr []int, low, high int) int {
	pivot := arr[high]
	i := low - 1
	
	for j := low; j < high; j++ {
		if arr[j] < pivot {
			i++
			arr[i], arr[j] = arr[j], arr[i]
		}
	}
	
	arr[i+1], arr[high] = arr[high], arr[i+1]
	return i + 1
}

// 归并排序实现
func Mergesort(arr []int, left, right int) {
	if left < right {
		mid := left + (right-left)/2
		
		Mergesort(arr, left, mid)
		Mergesort(arr, mid+1, right)
		
		merge(arr, left, mid, right)
	}
}

func merge(arr []int, left, mid, right int) {
	n1 := mid - left + 1
	n2 := right - mid
	
	// 创建临时数组
	L := make([]int, n1)
	R := make([]int, n2)
	
	// 复制数据到临时数组
	for i := 0; i < n1; i++ {
		L[i] = arr[left+i]
	}
	for j := 0; j < n2; j++ {
		R[j] = arr[mid+1+j]
	}
	
	// 合并临时数组
	i, j, k := 0, 0, left
	
	for i < n1 && j < n2 {
		if L[i] <= R[j] {
			arr[k] = L[i]
			i++
		} else {
			arr[k] = R[j]
			j++
		}
		k++
	}
	
	// 复制剩余元素
	for i < n1 {
		arr[k] = L[i]
		i++
		k++
	}
	
	for j < n2 {
		arr[k] = R[j]
		j++
		k++
	}
}
