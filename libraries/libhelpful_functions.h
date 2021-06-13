#ifndef libhelpful_functions
#define libhelpful_functions
 
//this function checks if every character in a cstring is a decimal (useful for atoi function)
//ignores new line character
int isstrdec(char * str);

//this function prompts a user to enter a series of integers for input into an array
//if the input cannot be converted into an integer, the input is ignored
//pass in the array and its size
void getintegers (int *arr, int arrsize);
 
#endif