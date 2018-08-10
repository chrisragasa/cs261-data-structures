#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TYPE createTask (int priority, char *desc) 
{
	TYPE newTask;
	newTask.priority = priority;
	strcpy(newTask.description, desc);
	return newTask;
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the 
			task priority, followed by a tab character (\t), and 
			the task description.
			
			The tasks are not necessarily stored in the file in 
			priority order. 
	
*/
void saveList(DynArr *heap, FILE *filePtr)
{
	//Check that the list exists and is not empty
  	assert(heap != 0);
  	assert(heap->size != 0);

  	//Create a pointer to tasks in the heap
  	Task * task = NULL;

  	//Write each task to the output file
  	for(int i = 0; i < heap->size; i++) {
  		task = &(heap->data[i]);
  		fprintf(filePtr, "%d\t%s\n", task->priority, task->description);
  	}
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file				
*/
void loadList(DynArr *heap, FILE *filePtr)
{
	char * nlptr;
 
 	assert(filePtr != 0);
 	assert(heap != 0);

 	char description[TASK_DESC_SIZE];
 	int priority;

 	//Loop through the contents of the file until EOF is reached
 	while(fscanf(filePtr, "%d\t", &priority) != EOF) {
 		fgets(description, sizeof(description), filePtr);

		/* remove trailing newline character */
		nlptr = strchr(description, '\r');
		if (nlptr) *nlptr = '\0';

		//Create the task and store it in item
 		TYPE item = createTask(priority, description);

 		//Add item to the heap
 		addHeap(heap, item);
 	}
}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
  	//Check that the heap exists and is not empty
  	assert(heap != 0);
  	assert(heap->size != 0);

  	//Create a temp heap that is sorted version of original
  	struct DynArr * tempDyn = newDynArr(heap->capacity);
  	copyDynArr(heap, tempDyn);
  	sortHeap(tempDyn);

  	//Create a pointer for element (Task) of the sorted temp heap
  	struct Task * task;

  	//Print out the sorted list
  	for(int i = tempDyn->size - 1; i >= 0; i--) {
  		task = &(tempDyn->data[i]);
  		printf("%d ", task->priority);
  		printf("%s\n", task->description);
  	}

  	//Free temp list
  	deleteDynArr(tempDyn);
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
	ret: 	-1 if priority of left < priority of right
			1 if priority of left > priority of right
			0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right)
{
	if (left.priority < right.priority)
		return -1;
	else if (left.priority > right.priority)
		return 1;
	else
		return 0;
}
