#include <stdio.h>
#include <stdlib.h>

#include "5_linked_lists.h"


int main()
{
	// Create a list object on the heap
	List *list = (List *)malloc(sizeof(List));
	
	// Test functions
	listInit(list, NULL);
	
	printf("List size after init: %d\n", listSize(list));
	
	free(list);
	return 0;
}
