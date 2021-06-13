#include <stdio.h>
#include "libraries/libhelpful_functions.h"

void bubblesort(int * arr, int count);

int main() {
	int arrsize = 10;
	int arr[arrsize];

	getintegers(arr, arrsize);

	//display array
	printf("The entered array is: ");
	for (int i = 0; i < arrsize; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	//sort the array
	bubblesort(arr, arrsize);

	//display the sorted array
	printf("The sorted array is: ");
	for (int i = 0; i < arrsize; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}

//bubble sort algorithm
void bubblesort(int * arr, int count) {
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}