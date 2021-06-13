#include <stdio.h>
#include <stdlib.h>
#include "./libhelpful_functions.h"

void getintegers (int *arr, int arrsize) {
	char userInput[10];
    int i = 0;

	//get the input array from the terminal
	printf("Enter the %d integers by pressing Enter after each (input that cannont be converted to number will be ignored, q to quit early):\n", arrsize);
	while (userInput[0] != 'q' && userInput[0] != 'Q' && i != arrsize) {
		fgets(userInput, 10, stdin);
		if (isstrdec(userInput)) {
			arr[i] = atoi(userInput);
			i++;
		};
	}
}