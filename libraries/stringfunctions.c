#include <string.h>
#include <ctype.h>

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