/* CS261- Assignment 1 - Q0 */
/* Name: Christopher Ragasa
 * Date: 1/22/18
 * Solution description: 
   This program was used as practice with pointer manipulation in C.
   It involved declaring an integer x, printing the address of x, 
   calling a function with the address of x as an argument, and 
   printing the value of x.
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
     printf("%d\n", *iptr);
     /*Print the address pointed to by iptr*/
     printf("%p\n", iptr);
     /*Print the address of iptr itself*/
     printf("%p\n", &iptr);
}

int main(){
    /*declare an integer x*/
    int x;
    /*print the address of x*/
    printf("%p\n", &x);
    /*Call fooA() with the address of x*/
    fooA(&x);
    /*print the value of x*/
    printf("%d\n", x);
    return 0;
}
