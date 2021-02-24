#include "shared.h"
#include <iostream>

int add(int a, int b) {
	return (a + b);
}

int subtract(int a, int b) {
	return (a - b);
}

int absDiff(int a, int b) {
	int c = a - b;
	if (c >= 0) {
		return c;
	} else {
		int d = a * b;
		a = d + b;
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

int isLoop(int n) {
	int counter = 0;
	for (int i = 0; i < n; i++) {
		counter++;
	}

	return counter;
}
