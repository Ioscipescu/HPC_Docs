#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define ARRAY_SIZE 10
int binarySearch(int arr[], int key, int begin, int end) {
	int mid_point = (begin + end) /2;
	if (arr[mid_point] == key) return mid_point;
	else if (abs(begin - end) == 1) return -1;
	else if (key > arr[mid_point]) return binarySearch(arr, key, mid_point + 1, end);
	else return binarySearch(arr, key, begin, mid_point - 1);
	return -1;
}
void insertionSort(int arr[], int n) {
	int i, j, key;
	for (i = 1; i < n; ++i) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && key < arr[j]) {
			arr[j+1] = arr[j];
			j = j - 1;
		}
		arr[j+1] = key;
	}
}
int main(int argc, char** argv) {
	static int arr[ARRAY_SIZE];
	time_t t;
	int i;
	size_t n = sizeof(arr)/sizeof(arr[0]);
	srand((unsigned) time(&t));
	for (i = 0; i < n; ++i) arr[i] = rand() % 50;
	int key = rand() % 50;
	int num_threads = omp_get_max_threads();
	int elms = ARRAY_SIZE / num_threads;
	int found_index = -1;
	printf("num_threads=%d\n", num_threads);
	#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		int index = tid * elms;
		int elements_left = (tid == num_threads - 1) ? ARRAY_SIZE - index : elms;
		int local[elements_left];
		for (int i = 0; i < elements_left; i++) local[i] = arr[index + i];
		insertionSort(local, elements_left);
		int local_index = binarySearch(local, key, 0, elements_left);
		if (local_index != -1) {
			int global_index = index + local_index;
			#pragma omp critical 
			{ 
				found_index = global_index; 
			}
		}
	}
	if (found_index == -1) printf("The key %d is not in the array.\n", key);
	else printf("The key %d is found at index %d.\n", key, found_index);
	return 0;
}
