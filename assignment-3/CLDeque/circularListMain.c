#include "circularList.h"
#include <stdio.h>

int main()
{	
	struct CircularList* deque = circularListCreate(); 
	circularListAddBack(deque, (TYPE)1);
	circularListAddBack(deque, (TYPE)2);
	circularListAddBack(deque, (TYPE)3);
	circularListAddFront(deque, (TYPE)4);
	circularListAddFront(deque, (TYPE)5);
	circularListAddFront(deque, (TYPE)6);
	circularListPrint(deque); // 4 5 6 sent 3 2 1

	
	printf("%g\n", circularListFront(deque));
	printf("%g\n", circularListBack(deque));
	
	circularListRemoveFront(deque);
	circularListRemoveBack(deque);
	circularListPrint(deque);
	
	circularListReverse(deque);

	circularListPrint(deque);
	
	circularListDestroy(deque);

	
	return 0;

}
