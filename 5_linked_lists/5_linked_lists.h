#ifndef LINKED_LISTS
#define LINKED_LISTS

#include <stdio.h>

/************************
 * STRUCTURES AND TYPES *
 ************************/

typedef struct ListElement_ {
	
	// Structure defining the element of a list. 
	// Contains a pointer to the data for this element, and then a pointer
	// to the next element
	
	void *data;
	struct ListElement_ *next;
	
} ListElement;


typedef struct List_ {
	
	// Keep track of the size of the list
	int size;
	
	// Function pointers to genericize the find and destroy functions
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	
	// Pointers to the top and bottoms of the list. 
	// Keeping track of the tail means that an append action is O(1)
	ListElement *head;
	ListElement *tail;
	
} List;

/******************************
 * PUBLIC INTERFACE FUNCTIONS *
 ******************************/

// O(1) - Sets initial settings for a list object
void listInit(List *list, void (*destroy)(void *data));

// O(n) - Iterates over the elements in a list calling the destroy function
//        provided in listInit
void listDestroy(List *list);

// O(1) - Inserts a list element directly subsequent to the specified element
int listInsertNext(List *list, ListElement *element, const void *data);

// O(1) - Removes the list element directly subsequent to the specified element
int listRemoveNext(List *list, ListElement *element, void **data); 

/***************************
 * PUBLIC INTERFACE MACROS *
 ***************************/

#define listSize(list) ((list)->size)

#define listHead(list) ((list)->head)

#define listTail(list) ((list)->tail)

#define listIsHead(list, element) ((element) == (list)->head ? 1 : 0)

#define listIsTail(element) ((element)->next == NULL ? 1 : 0)

#define listData(element) ((element)->data)

#define listNext(element) ((element)->next)

#endif
