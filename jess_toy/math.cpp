#include "shared.h"
#include <iostream>

int add(int a, int b) {
	return (a + b);
}

int subtract(int a, int b) {
	return (a - b);
}

int absVal(int a, int b) {
	int c = a - b;
	if (c >= 0) {
		return c;
	} else {
		return -1 * c;
	}
}

int isPos(int a) {
	if (a > 0) {
		return 1;
	} else {
		return 0;
	}
}
