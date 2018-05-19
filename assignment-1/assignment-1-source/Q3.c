/* CS261- Assignment 1 - Q3 */
/* Name: Christopher Ragasa
 * Date: 1/22/18
 * Solution description:
   Generate an array of random integers and sort them in ascending order.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//swap and sort algorithm are cited from geeksforgeeks.org
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int* number, int n) {
     /*Sort the given array number , of length n*/
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (number[j] < number[min_idx])
                min_idx = j;

        // Swap the found minimum element with the first element
        swap(&number[min_idx], &number[i]);
    }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;

    /*Allocate memory for an array of n integers using malloc.*/
    int * myArray = malloc(n * sizeof(int));
    
    /*Fill this array with random numbers, using rand().*/
    for(int i = 0; i < n; i++) {
        int random = rand() % 100;
        myArray[i] = random;
    }
    /*Print the contents of the array.*/
    for(int i = 0; i < n; i++) {
        printf("%d", myArray[i]);
        printf(" ");
    }

    /*Pass this array along with n to the sort() function of part a.*/
    sort(myArray, n);


    /*Print the contents of the array.*/
    printf("\n");
    for(int i = 0; i < n; i++) {
        printf("%d", myArray[i]);
        printf(" ");
    }

    return 0;
}
