#include <stdlib.h>
#include <string.h>

#include "5_linked_lists.h"


/* Functions from external libraries:
 * 
 * String.h
 *     memset()
 * 
 * Stdlib.h
 *     malloc()
 *     free()
 * 
 */

void listInit(List *list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
	
	return;
}

void listDestroy(List *list)
{
	void *data;                                         // Create variable to hold list item after removing from tail
	
	while(listSize(list) > 0)                           // While there is data in the list
	{
		if(
		listRemoveNext(list, NULL, (void **)&data) == 0 // If the pop data off the end of tail and point local data variable to it function worked
		&&                                              // and
		list->destroy != NULL                           // the list destroy function is valid
		)
		{
			list->destroy(data);                        // Destroy data with user-provided function
		}
	}
	
	memset(list, 0, sizeof(List));                      // Zero out the memory area of the List object (just in case)
	
	return;
}

int listInsertNext(List *list, ListElement *element, const void *data)
{
	ListElement *new_element;
	
	
	
	return 0;
}

int listRemoveNext(List *list, ListElement *element, void **data)
{
	ListElement *old_element;
	
	// Can't remove items from a list if there are no items. 
	if(listSize(list) == 0)_
	{
		return -1;                             // Return -1 for error, list already empty
	}
	
	// Remove item if it is the head
	// Since there is no element preceding the head, NULL is submitted to this function to call for this  subprocedure. 
	if(element == NULL)
	{
		*data = list->head->data;              // Point data variable from calling function to data element in re
		old_element = list->head;              // Point old_element to the head item
		list->head = list->head->next;         // Point head pointer to second item in list
		
		if(listSize(list) == 1)
		{
			list->tail = NULL;                 // If the list only has one element now, set tail to NULL
		}
	}
	
	// Remove item if it not head
	else 
	{
		if(element->next == NULL)
		{
			return -1;                        // Return -1 for error if there is no item "next" to the provided element to remove (e.g. submitted the tail element as the preceding element of the element to remove)
		}
		*data = element->next->data;          // Otherwise, point data to the element that's being removed's data 
		old_element = element->next;          // Point old_element to the element being removed
		element->next = element->next->next;  // Poing the this element's next element pointer to the next element's next element pointer
	}
	
	free(old_element);                        // Free the old_element's HEAP memory if allocated
	
	list->size--;                             // Decrement list's size since an element has been removed (otherwise function would have returned earlier with -1
	
	return 0;                                 // Return 0 for success. 
	
}
