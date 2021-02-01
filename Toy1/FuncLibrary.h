#pragma once

#include <iostream>
#include <string>
using namespace std;

#ifdef FUNCLIBRARY_EXPORTS
#define FUNCLIBRARY_API __declspec(dllexport)
#else
#define FUNCLIBRARY_API __declspec(dllimport)

#endif


// The Fibonacci recurrence relation describes a sequence F
// where F(n) is { n = 0, a
//               { n = 1, b
//               { n > 1, F(n-2) + F(n-1)
// for some initial integral values a and b.
// If the sequence is initialized F(0) = 1, F(1) = 1,
// then this relation produces the well-known Fibonacci
// sequence: 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

// Initialize a Fibonacci relation sequence
// such that F(0) = a, F(1) = b.
// This function must be called before any other function.
extern "C" FUNCLIBRARY_API void fibonacci_init(
    const unsigned long long a, const unsigned long long b);

// Produce the next value in the sequence.
// Returns true on success and updates current value and index;
// false on overflow, leaves current value and index unchanged.
extern "C" FUNCLIBRARY_API bool fibonacci_next();

// Get the current value in the sequence.
extern "C" FUNCLIBRARY_API unsigned long long fibonacci_current();

// Get the position of the current value in the sequence.
extern "C" FUNCLIBRARY_API unsigned fibonacci_index();

extern "C" FUNCLIBRARY_API int add(int a, int b);   // returns a + b 

extern "C" FUNCLIBRARY_API int sub(int a, int b);   // returns the greater of the two a - b or b - a

extern "C" FUNCLIBRARY_API void starTrees(int a);   // prints pyramid of stars height a

extern "C" FUNCLIBRARY_API string hello(string a);  // returns hello + " " + string 

extern "C" FUNCLIBRARY_API string meetCatWalk();    // returns our names 

extern "C" FUNCLIBRARY_API void print(string a);    // prints string 