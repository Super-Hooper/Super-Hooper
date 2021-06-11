#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isstrdec(char * str);
void bubblesort(int * arr, int count);

int main() {
	char userInput[10];
	int arr[100];
	int count = 0;

	//get the input array from the terminal
	printf("Enter an array of integers by pressing Enter after each (q to quit):\n");
	fgets(userInput, 10, stdin);
	do {
		if (isstrdec(userInput)) {
			arr[count] = atoi(userInput);
			count++;
		};
		fgets(userInput, 10, stdin);
	} while (userInput[0] != 'q' && userInput[0] != 'Q');

	//display array
	printf("The entered array is: ");
	for (int i = 0; i < count; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	//sort the array
	bubblesort(arr, count);

	//display the sorted array
	printf("The sorted array is: ");
	for (int i = 0; i < count; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}

//check if every character is a digit
//discard newline character if present
int isstrdec(char * str) {
	int isdec = 1;
	for (int i = 0; i < strlen(str); i++) {
		if (!isdigit(str[i]) && str[i] != '\n')
			isdec = 0;
	}
	return isdec;
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