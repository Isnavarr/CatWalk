#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
	extern int add();
	extern int subtract(int a, int b);
	extern int absVal(int a, int b);
	extern int isPos(int a);

	extern void printName(char* name);

#ifdef __cplusplus
}
#endif

#endif
