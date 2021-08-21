#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Because I want to display some of the results of the functions written below, I have
// to declare them up front or write the code up front.
// I like the cleaner look of having the main function first though. 
int arrays();
int rightSwap(int *x, int *y);
int genericPointersSwap(void *ptra, void *ptrb, int size);
int charToInt(char c);
int functionPointerExample(int x, int y);

int main()
{
	//printf("Value 0 from arrays: %d\n", arrays());
	
	int x = 5;
	int y = 7;
	printf("Pre Swap X and Y: %d   %d\n", x, y);
	
	// The ampersand sign here tells the compiler to submit the ADDRESSES of
	// these variables rather than the value. It is the "reference" symbol
	rightSwap(&x, &y);
	
	printf("Post swap X and Y: %d   %d\n", x, y);
	
	printf("=== Lets do this again but with a generalized function ===\n");
	
	x = 5;
	y = 7;
	printf("Pre Swap X and Y: %d   %d\n", x, y);
	
	genericPointersSwap(&x, &y, sizeof(int));
	
	printf("Post swap X and Y: %d   %d\n", x, y);
	
	printf("=== What does the letter F look like as an int? ===\n");

	char c = 'F';
	printf("%d\n", charToInt(c));
	
	printf("=== Does a function pointer realy work? ===\n");
	
	if(functionPointerExample(12,12))
	{
		printf("True\n");
	}
	else
	{
		printf("False\n");
	}
	
	return 0;
}

// Bad pointer

int badPointer(int **ptr)
{
	int a = 10;
	// Pointing pointer to an address on the stack that will become invalid
	// when the function returns, making any other function that relys on
	// iptr develop "undefined behaviour" 
	*ptr = &a;
	
	return 0;
}

// Good pointer

int goodPointer(int **ptr)
{
	// The if statement and comparison to NULL is only to check if malloc
	// failed.. 
	// Here we point ptr to an address assigned my malloc on the heap. This
	// survives the function's return and ptr remains a valid pointer
	if( (*ptr = (int *)malloc(sizeof(int))) == NULL)
	{
		return -1;
	}
	// This can create problems if *ptr is not freed later leading to memory leaks.
	return 0;
}

// Arrays

int arrays()
{
	// A C array is just a STATIC POINTER to the first element of the array
	// Here, we create an array with 10 elements. The array variable itself is
	// equivilent to the ptr variable, just with 10 consecutive blocks of sizeof(int)
	// memory reserved at the memory address pointed to in array
	int array[10];
	int *ptr;
	
	// Here we set ptr to the same address as array and then use it as if
	// it were an array
	ptr = array;
	// The following 2 manners of assigning values are effectively identical
	*ptr = 5;
	ptr[0] = 5;
	
	return ptr[0];
}

// Call by reference

int wrongSwap(int x, int y)
{
	// Because the items were passed in as values, the swap does not last the 
	// function return
	int temp;
	temp = x;
	x = y;
	y = temp;
	
	return 0;
}

int rightSwap(int *x, int *y)
{
	// In this variant, the item's memory addresses are called submitteed
	// by the caller. Then this function goes into those addresses
	// and updates the values for the caller, surviving the return
	int temp;
	
	// The pointer symbol (*) in this case "dereference" the pointer telling
	// the compiler to look at the VALUE at the ADDRESS and NOT the address
	// itself. 
	temp = *x;
	*x = *y;
	*y = temp;
	
	return 0;
}

// Generic pointers

int genericPointersSwap(void *ptra, void *ptrb, int size)
{
	// Generic/void pointers are pointers that can contain the address of
	// any type of data because it's unspecified. 
	// This is useful when the underlying does not care about the value the pointer 
	// is pointing to such as a copy function or a swap function
	
	void *temp;
	if( (temp = malloc(size)) == NULL)
	{
		return -1;
	}
	
	// Copy stuff at ptra to temp
	memcpy(temp, ptra, size);
	// Copy stuff from ptrb to ptra
	memcpy(ptra, ptrb, size);
	// Copy stuff from temp to ptrb
	memcpy(ptrb, temp, size);
	
	// Free temp to avoid memory leaks
	free(temp);
	
	return 0;
}

// Casts

int charToInt(char c)
{
	// Casts are how we change the type of a value in C.
	// Here, we're returning what char c looks like as an int. 
	return (int)c;
}

// Function pointers (distinct from functions that return pointers)

int functionPointerExample(int x, int y)
{
	// Function pointers can be used to point to any function that has a
	// similar structure. 
	
	// This is how we declare a function pointer
	int (*match)(void *a, void *b);
	// This function pointer can now be pointed to any function that accepts
	// 2 void pointers and returns an integer
	
	int matchInt(void *a, void *b)
	{
		// Pointer wizardry
		// Let me explain and break it down
		// Becausee a is a void *, we have to cast it as an int *
		// Then, we want to dereference it to look at the value
		// so we get "dereference" "cast as int pointer" "void pointer"
		//                 *              (int *)             a
		// 
		if(*(int *)a == *(int *)b)
		{
			return 1;
		}
		return 0;
	}
	
	// Now we can point the match function pointer to the address of the function 
	// matchInt in memory
	match = matchInt;
	
	// Now we can use match as if it were matchInt
	return match(&x, &y);
}


