

/*
 * This is the file in which you'll write the functions required to implement
 * a stack using two queues.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Christopher Ragasa
 * Email: ragasac@oregonstate.edu
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#define TYPE int

struct link {
	TYPE value;
	struct link * next;
};

struct listQueue {
	struct link * firstLink;
	struct link * lastLink;
};

struct myStack {
	struct listQueue * q1;
	struct listQueue * q2;
};

void listQueueInit(struct listQueue * q) {
	struct link * lnk = (struct link *) malloc(sizeof(struct link));
	assert(lnk != 0); 
	lnk->next = 0;
	q->firstLink = q->lastLink = lnk;
}

void listQueueAddBack (struct listQueue *q, TYPE e) {
	struct link * newLink = (struct link *) malloc(sizeof(struct link));
	assert(newLink != 0);

	q->lastLink->next = newLink;
	q->lastLink = newLink;

	newLink->value = e;
	newLink->next = NULL;
}

TYPE listQueueFront(struct listQueue *q) {
	assert(q->firstLink != q->lastLink);
	return q->firstLink->next->value;
}

void listQueueRemoveFront(struct listQueue *q) {
	assert(q->firstLink != q->lastLink);
	struct link * temp = q->firstLink->next;

	if(q->firstLink->next == q->lastLink) {
		q->lastLink = q->firstLink;
		q->firstLink->next = NULL;
	} else {
		q->firstLink->next = q->firstLink->next->next;
	}
	free(temp);
	temp = NULL;
}

int listQueueIsEmpty(struct listQueue * q) {
	if(q->firstLink == q->lastLink) {
		return 1;
	} else {
		return 0;
	}
}

//*****************

void printQueue(struct listQueue * q) {
	if(q->firstLink == q->lastLink) {
		printf("%s", "ERROR: Can't print. The stack is empty.");
	} else {
		struct link * iterator = q->firstLink;
		do {
			printf("%d", iterator->next->value);
			iterator = iterator->next;
		} while(iterator->next != NULL); 
	}
}

void linkedListStackPush(struct myStack * s, TYPE val) {
	//Push val to end of 
	if(listQueueIsEmpty(s->q1) == 1) {
		s->q1 = (struct listQueue *) malloc(sizeof(struct listQueue));
		listQueueInit(s->q1);
	}
	listQueueAddBack(s->q1, val);
}

void linkedListStackPop(struct myStack * s) {
	//Check that the list isn't empty
	assert(listQueueIsEmpty(s->q1) != 1);

	//Store location of primary queue
	struct listQueue * q1temp = s->q1;

	//Transfer all values except last into the secondary queue
	
	if(s->q1->firstLink->next->next == NULL) {
		listQueueRemoveFront(s->q1);
	} else {
		while(s->q1->firstLink->next->next != NULL) {
			listQueueAddBack(s->q2, s->q1->firstLink->next->value);
			listQueueRemoveFront(s->q1);		
		}
		listQueueRemoveFront(s->q1);
	}



	s->q1 = s->q2;
	s->q2 = q1temp;
	
	
}

TYPE linkedListStackTop(struct myStack * s) {
	assert(listQueueIsEmpty(s->q1) != 1);
	return s->q1->lastLink->value;
}

int linkedListStackIsEmpty(struct myStack * s) {
	return listQueueIsEmpty(s->q1);
}


int main() {
	//Create stack
	struct myStack * s = (struct myStack *) malloc(sizeof(struct myStack));

	//Allocate memory for 2 queues in stack
	s->q1 = (struct listQueue *) malloc(sizeof(struct listQueue));
	s->q2 = (struct listQueue *) malloc(sizeof(struct listQueue));

	//Initialize the 2 queues in stack
	listQueueInit(s->q1);
	listQueueInit(s->q2);

	//Add some test values 
	linkedListStackPush(s, 1);
	linkedListStackPush(s, 2);
	linkedListStackPush(s, 3);
	linkedListStackPush(s, 4);

	printf("%s", "Before Pop:");
	printQueue(s->q1);
	

	printf("%s", "After Top:");
	//printf("%d", linkedListStackIsEmpty(s));
	
	linkedListStackPop(s);
	printf("%d", linkedListStackTop(s));
	//linkedListStackPush(s, 5);
	//linkedListStackPop(s);
	//linkedListStackPop(s);
	//linkedListStackPop(s);
	//linkedListStackPop(s);
	//printQueue(s->q1);

	


	return 0;
}
