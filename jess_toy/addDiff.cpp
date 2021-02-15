#include<iostream> 
#include<stdlib.h>
#include<stdio.h>
#include "shared.h"

using namespace std; 


int addDiff(int num)
{
	int newNum = 0; 
	
	//if num == 0 add a random number
	if (num == 0) 
	{
		newNum = rand() % 5;
		num = num + newNum;
	}
	
	//if num >= 10 multiply and add a random number
	else if (num > 10 || num == 10)
	{
		newNum = (rand() % 20); 
		num = (num * newNum); 
		num = (num + newNum); 

	}
	
	//if num > 100 add 1 + 2 +...+ (num % 100) 
	else if (num > 100) 
	{
		for (int j = 0; j < (num%100); j++) 
		{
			num = num + j; 
		}
	}
	//if num is odd add one
	else if (num % 2 == 1) 
	{
		num++; 
	}
	
	return num; 
}
/*
int main ()
{
	int secret[] = {0, 4, 7, 10, 29, 164}; 
	int a = 0; 
	for (int i = 0; i < 6; i++) 
	{
		a = addDiff(secret[i]); 
		cout << a << endl; 
	}
	return 0; 
}
*/
