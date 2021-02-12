#include <stdio.h>
#include "shared.h"

int main(void) {

	printf("The result is [%d]\n", add());
	
	int c = 5;
	int d = 3;
	int result2 = subtract(c,d);

	printf("The result is [%d]\n", result2);

	result2 = absVal(d,c);
	printf("absval is [%d]\n", result2);

	printf("Is -3 positive? [%d]\n", isPos(-3));

	char name[12] = "Jessica";
	printName(name);

	return 0;
}
