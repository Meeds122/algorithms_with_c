#include <stdio.h>
#include <stdlib.h>

int factorial(int n);
int factorialTail(int n, int a);

int main()
{
	printf("=== What is the factorial of 4? ===\n");
	printf("%d\n", factorial(4));
	printf("Using tail recursion?\n");
	printf("%d\n", factorialTail(4, 1));
	return 0;
}

// Basic Recursion

int factorial(int n)
{
	// These basic recursion functions grow within the stack as the number
	// of functions calls increase, greatly increasing memory demands
	
	// Error condition
	if(n < 0)
	{
		return -1;
	}
	// End condition. This is what starts the unwinding of the function
	// calls. Both 1! and 0! are defined as 0
	if(n == 1 || n == 0)
	{
		return 1;
	}
	return n * factorial(n-1);
}

// Tail Recursion

int factorialTail(int n, int a)
{
	// Tail recursion is optimized by modern compilers by removing old function
	// call stack framse. 
	// This type of recursion is characterized by having nothing
	// to do during the unwinding phase. 
	// Technically, "A recursive call is tail recursive when  it is the 
	// last statement that will be executed within the body of a function 
	// and its return value is not part of an expression"
	// e.g. n * factorial(n-1) is an example of an expression from factorial()
	// 
	// In this case, we have the variable, a, which is keeping track of 
	// the value computed so far. 
	
	// Error handling
	if(n < 0)
	{
		return -1;
	}
	
	// Handle out of bounds behaviour. 0! is defined as 1
	else if(n == 0)
	{
		return 1;
	}
	
	// End condition
	else if(n == 1)
	{
		return a;
	}
	
	// Tail recursion
	else
	{
		return factorialTail(n - 1, n * a);
	}
	// Here, factorialTail is the last statement executed in the function. 
	// There is no more work here to do for the rest of the functions all the
	// way up the call stack. 
}
