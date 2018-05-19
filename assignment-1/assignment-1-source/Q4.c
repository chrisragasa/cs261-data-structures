/* CS261- Assignment 1 - Q4 */
/* Name: Christopher Ragasa
 * Date: 1/22/18
 * Solution description:
   Sort an array of student structures.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

//swap and sort algorithm are cited from geeksforgeeks.org
void swap(struct student * xp, struct student * yp)
{
    struct student temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(struct student* students, int n){
    /*Sort the n students based on their score*/
    /*Sort the given array number , of length n*/
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (students[j].score < students[min_idx].score)
                min_idx = j;

        // Swap the found minimum element with the first element
        swap(&students[min_idx], &students[i]);
    }
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 10;

    /*Allocate memory for n students using malloc.*/
    struct student * studentArray = malloc(n * sizeof(struct student));
    
    /*Generate random and unique IDs and random scores for the n students, using rand().*/
    for(int i = 0; i < 10; i++) {
        int randomID;
        randomID = rand() % 10;     //generate random number

        for(int i = 0; i < 10; i++) {       //check if random number is being used by a different student
            while(randomID == studentArray[i].id) {
                randomID = rand() % 10;     //if random number is already being used, generate new random number
            }
        }

        int randomScore;
        randomScore = rand() % 100;

        studentArray[i].id = randomID;
        studentArray[i].score = randomScore;
    }

    /*Print the contents of the array of n students.*/
    for(int i = 0; i < 10; i++) {
        printf("%d", studentArray[i].id);
        printf("%s", " ");
        printf("%d", studentArray[i].score);
        printf("\n");
    }

    /*Pass this array along with n to the sort() function*/
    sort(studentArray, n);

    /*Print the contents of the array of n students.*/
    printf("\n");
    for(int i = 0; i < 10; i++) {
        printf("%d", studentArray[i].id);
        printf("%s", " ");
        printf("%d", studentArray[i].score);
        printf("\n");
    }

    return 0;
}
