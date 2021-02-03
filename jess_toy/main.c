#include <stdio.h>
#include "shared.h"

int main(void) {
	unsigned int a = 1;
	unsigned int b = 2;
	unsigned int result1 = add(a,b);

	printf("The result is [%u]\n", result1);
	
	int c = 5;
	int d = 3;
	int result2 = subtract(c,d);

	printf("The result is [%d]\n", result2);

	char name[12] = "Jessica";
	printName(name);

	return 0;
}
