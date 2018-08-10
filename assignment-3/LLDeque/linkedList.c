#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// FIXME: you must write this
	
	//Initialize front and back sentinels.
	struct Link * front = (struct Link *) malloc(sizeof(struct Link));
	struct Link * back = (struct Link *) malloc(sizeof(struct Link));

	front->prev = NULL;
	front->next = back;
	back->prev = front;
	back->next = NULL;

	list->frontSentinel = front;
	list->backSentinel = back;

	//Initilize size of the linked list.
	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this

	//Create the new link
	struct Link * newLink = (struct Link *) malloc(sizeof(struct Link));

	//Initialize newLink
	newLink->value = value;
	newLink->next = link;
	newLink->prev = link->prev;

	//Reassign link
	link->prev = newLink;
	link->prev->next = newLink;

	//Update size
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this

	//Create a temporary pointer to hold location of link.
	struct Link * temp = link;

	//Reassign values of surrounding links.
	link->prev->next = link->next;
	link->next->prev = link->prev;

	//Free temp.
	free(temp);

	//Decrement size of list.
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	//Create a new link.
	struct Link * newLink = (struct Link *) malloc(sizeof(struct Link));

	//Initialize newLink.
	newLink->next = list->frontSentinel->next;
	newLink->prev = list->frontSentinel;
	newLink->value = value;

	//Reassign surrounding links.
	list->frontSentinel->next->prev = newLink;
	list->frontSentinel->next = newLink;

	//Update size.
	list->size++;
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	//Create a new link.
	struct Link * newLink = (struct Link *) malloc(sizeof(struct Link));

	//Initialize newLink.
	newLink->prev = list->backSentinel->prev;
	newLink->next = list->backSentinel;
	newLink->value = value;

	//Reassign surrounding links.
	list->backSentinel->prev->next = newLink;
	list->backSentinel->prev = newLink;

	//Update size.
	list->size++;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this
	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this
	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this
	//Create temp pointer to store location of link after front sentinel.
	struct Link * temp = list->frontSentinel->next;

	//Reassign pointers of surrounding links.
	list->frontSentinel->next->next->prev = list->frontSentinel;
	list->frontSentinel->next = list->frontSentinel->next->next;

	//Free old link.
	free(temp);

	//Update size.
	list->size--;

}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this
	//Create temp pointer to store location of link before back sentinel.
	struct Link * temp = list->backSentinel->prev;

	//Reassign pointers of surrounding links.
	list->backSentinel->prev->prev->next = list->backSentinel;
	list->backSentinel->prev = list->backSentinel->prev->prev;

	//Free old link.
	free(temp);

	//Update size.
	list->size--;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this
	if(list->size <= 0) return 1;
	else return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	
	// FIXME: you must write this
	
	//Check that the list isn't empty.
	assert(list->size != 0);

	//Create a pointer (pointer to first value) that will cycle through the list.
	struct Link * ptr = list->frontSentinel->next;

	//Print all the elements in the list.
	do {
		printf("%d", ptr->value);
		ptr = ptr->next;
	} while(ptr->next != 0);

}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	//Create a new link.
	struct Link * newLink = (struct Link *) malloc(sizeof(struct Link));

	//Initialize newLink.
	newLink->prev = list->frontSentinel;
	newLink->next = list->frontSentinel->next;
	newLink->value = value;

	//Reassign surroudning links.
	list->frontSentinel->next->prev = newLink;
	list->frontSentinel->next = newLink;

	//Update size;
	list->size++;
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	
	// FIXME: you must write this
	//Check that the list isn't empty.
	assert(list->size != 0);

	//Create a pointer (pointer to first value) that will cycle through the list.
	struct Link * ptr = list->frontSentinel->next;

	//Check through all elements in the list.
	do {
		if(ptr->value == value) return 1;
		ptr = ptr->next;
	} while(ptr->next != 0);
	
	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	
	// FIXME: you must write this
	//Check that the list isn't empty.
	assert(list->size != 0);

	//Create a pointer (pointer to first value) that will cycle through the list.
	struct Link * ptr = list->frontSentinel->next;

	//Check through all elements in the list.
	do {
		if(ptr->value == value) {
			removeLink(list, ptr);
			break;
		}
		ptr = ptr->next;
	} while(ptr->next != 0);

}



