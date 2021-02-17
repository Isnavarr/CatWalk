#include <stdio.h>
#include <iostream>
#include "shared.h"

int main(void) {
	int a;
	int b;
	std::cout << "A val: ";
	std::cin >> a;
	std::cout << "B val: ";
	std::cin >> b;
	printf("add is [%d]\n", add(a, b));
	
	int result2 = subtract(a,b);

	printf("subtract is [%d]\n", result2);

	result2 = absDiff(a,b);
	printf("absdiff is [%d]\n", result2);

	printf("loop: %d\n", isLoop(4));

	printf("Is -3 positive? [%d]\n", isPos(-3));

	char name[12] = "Jessica";
	printName(name);

	return 0;
}
