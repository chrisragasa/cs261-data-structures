/* CS261- Assignment 1 - Q2 */
/* Name: Christopher Ragasa
 * Date: 1/22/18
 * Solution description:
   This program demonstrates the concept of passing by value.
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;
    /*Set b to half its original value*/
    *b = *b / 2;
    /*Assign a+b to c*/
    c = *a + *b;
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;

    /*Print the values of x, y and z*/
    printf("%d", x);
    printf("\n");
    printf("%d", y);
    printf("\n");
    printf("%d", z);
    printf("\n");

    /*Call foo() appropriately, passing x,y,z as parameters*/
    /*Print the value returned by foo*/
    printf("%d", foo(&x, &y, z));
    printf("\n");

    /*Print the values of x, y and z again*/
    printf("%d", x);
    printf("\n");
    printf("%d", y);
    printf("\n");
    printf("%d", z);
    printf("\n");

    /*Is the return value different than the value of z?  Why?*/

    /*Yes, the return value is different. Although in foo() we are returning c, the actual value of c does not change
     * as it is passed by value. This is shown by how the value of c stays at 7 even after calling foo(). */
 return 0;
}
    
    
