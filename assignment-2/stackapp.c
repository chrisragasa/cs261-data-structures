/* CS261- Assignment 2 */
/* Name: Christopher Ragasa
 * Date: 1/25/18
 * Solution description:
   Stack implementation to check for unbalanced parentheses.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	
	//Check if the character s is null.
	assert(s != NULL);

	//Create an array with capacity of length
	DynArr * stack;
	stack = newDynArr(2);

	char a;

	do {

		a = nextChar(s);

		if(a == '(') addDynArr(stack, ')');
		else if(a == '{') addDynArr(stack, '}');
		else if(a == '[') addDynArr(stack, ']');

		else if(a == ')') {
			if(sizeDynArr(stack) == 0) {
				deleteDynArr(stack);
				return 0;
			}
			else if(topDynArr(stack) == ')') {
				popDynArr(stack);
			}
			else {
				deleteDynArr(stack);
				return 0;
			}
		}

		else if(a == '}') {
			if(sizeDynArr(stack) == 0) {
				deleteDynArr(stack);
				return 0;
			}
			else if(topDynArr(stack) == '}') {
				popDynArr(stack);
			}
			else {
				deleteDynArr(stack);
				return 0;
			}
		}

		else if(a == ']') {
			if(sizeDynArr(stack) == 0) {
				deleteDynArr(stack);
				return 0;
			}
			else if(topDynArr(stack) == ']') {
				popDynArr(stack);
			}
			else {
				deleteDynArr(stack);
				return 0;
			}
		}

	} while (a != '\0');

	if(sizeDynArr(stack) == 0) {
		freeDynArr(stack);
		return 1;
	}
	else {
		freeDynArr(stack);
		return 0;
	}

}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

