#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>

#ifdef __cpplusplus
extern "C" {
#endif
	extern unsigned int add(unsigned int a, unsigned int b);
	extern int subtract(int a, int b);

	extern void printName(char* name);

#ifdef __cplusplus
}
#endif

#endif
