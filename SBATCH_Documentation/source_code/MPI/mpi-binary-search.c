#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#define ARRAY_SIZE 10
int binarySearch(int arr[], int key, int begin, int end) {
	int mid_point = (begin + end) / 2;
	if(arr[mid_point] == key) return mid_point;
	else if(abs(begin - end) == 1) return -1;
	else if(key > arr[mid_point]) return binarySearch(arr, key, mid_point + 1, end);
	else return binarySearch(arr, key, begin, mid_point - 1);
	return -1;
}
void insertionSort(int arr[], int n) {
	int i, j, key;
	for(i = 1; i < n; ++i) {
		key = arr[i];
		j = i - 1;
		while(j >= 0 && key < arr[j]) {
			arr[j + 1] = arr[j];
			j = j  - 1;
		}
		arr[j + 1] = key;
	}
}
int main(int argc, char** argv) {
	static int arr[ARRAY_SIZE];
	time_t t;
	int i;
	size_t n = sizeof(arr)/sizeof(arr[0]);
	MPI_Status status;
	MPI_Init(&argc, &argv);
	int pid;
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	int number_of_processes;
	MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);
	if (pid == 0) {
		srand((unsigned) time(&t));
		for( i = 0 ; i < n ; ++i ) arr[i] = rand() % 50;
		int index, i;
		int elms;
		srand((unsigned) time(&t));
		int key = rand() % 50;
		elms = ARRAY_SIZE / number_of_processes;
		if (number_of_processes > 1) {
			for (i = 1; i < number_of_processes - 1; i++) {
				index = i * elms;
				MPI_Send(&key, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				MPI_Send(&elms, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				MPI_Send(&arr[index], elms, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
			index = i * elms;
			int elements_left = ARRAY_SIZE - index;
			MPI_Send(&key, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&elements_left, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&arr[index], elements_left, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		insertionSort(arr, elms);
		index = binarySearch(arr, key, 0, elms);
		if (index == - 1)
			for (i = 1; i < number_of_processes; i++) {
				MPI_Recv(&index, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
				if (index == -1) printf("the key %d is not in the array\n", key);
				else printf("the key %d is found in the array\n", key);
			}
		else printf("the key %d is found in the array\n", key);
	} else {
		int key = 0;
		MPI_Recv(&key, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		int recv = 0;
		MPI_Recv(&recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		int buffer[recv];
		size_t n = sizeof(buffer)/sizeof(buffer[0]);
		MPI_Recv(&buffer, recv, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		insertionSort(buffer, n);
		int index = binarySearch(buffer, key, 0, n);
		MPI_Send(&index, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
