#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this

	//Allocate memory for sentinel
	list->sentinel = malloc(sizeof(struct Link));

	//Initialize sentinal
	list->sentinel->prev = list->sentinel;
	list->sentinel->next = list->sentinel;

	//Initialize list
	list->size = 0;
	list->sentinel->value = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this

	//Allocate memory for newLink
	struct Link * newLink = (struct Link *) malloc(sizeof(struct Link));

	//Initialize newLink
	newLink->value = value;
	newLink->next = NULL;
	newLink->prev = NULL;

	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	
	//Allocate memory for newLink
	struct Link * newLink = createLink(value);

	//Initialize newLink
	newLink->prev = link;
	newLink->next = link->next;

	//Reassign surrounding links
	newLink->next->prev = newLink;
	newLink->prev->next= newLink;

	//Update size
	list->size++;

}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this
	// [] [] []

	//Reassign surrounding links
	link->next->prev = link->prev;
	link->prev->next = link->next;

	//Free link
	free(link);
	link = NULL;
	//temp = NULL;

	//Update size
	list->size--;

}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list) {
	while (!circularListIsEmpty(list)) {
		struct Link * temp = list->sentinel->next;
		removeLink(list, temp);
	}
	free(list->sentinel);
	free(list);

}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list->size != 0);
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list->size != 0);
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
	removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */



int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
	//printf("%g", list->size);
	
	//assert(list != NULL);
	if((list->size == 0) && (list->sentinel->next == list->sentinel))  {
		return 1; 
	} else {
		return 0;
	}
	
	
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	assert(!circularListIsEmpty(list));
	assert(list != NULL);
	assert(list->size != 0);

	//Create temp ptr that points to first node after sentinel
	struct Link * temp = list->sentinel->next;
	
	for(int i = 0; i < list->size; i++) {
		printf("%f", temp->value);
		temp = temp->next;
	}
}
	

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	
	// FIXME: you must write this
	assert(list != NULL);
	assert(list->size != 0);

	struct Link * current = list->sentinel;
	
	for(int i = 0; i < list->size + 1; i++) {
		//temp pointer to current node
		struct Link * temp = current->next;

		current->next = current->prev;
		current->prev = temp;
		current = current->next;
	}		   
}

