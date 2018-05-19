/* CS261- Assignment 1 - Q1 */
/* Name: Christopher Ragasa
 * Date: 1/22/18
 * Solution description:
   This program demonstrates memory allocation in C. The program shows how to allocate
   memory for students, generate random IDs and scores for each student, print data for 
   each student, and free memory.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
    struct student * studPtr = (struct student*) malloc(10 * sizeof(struct student));
     /*return the pointer*/
    return studPtr;
}


void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    for(int i = 0; i < 10; i++) {
        int randomID;
        randomID = rand() % 10;     //generate random number

        for(int i = 0; i < 10; i++) {       //check if random number is being used by a different student
            while(randomID == students[i].id) {
                randomID = rand() % 10;     //if random number is already being used, generate new random number
            }
        }

        int randomScore;
        randomScore = rand() % 100;

        students[i].id = randomID;
        students[i].score = randomScore;
    }

}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/

    for(int i = 0; i < 10; i++) {
        printf("%d", students[i].id);
        printf("%s", " ");
        printf("%d", students[i].score);
        printf("\n");
    }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
    int min = 101;
    int max = -1;
    int sum = 0;
    float average = 0;

    //check for min values
    for(int i = 0; i < 10; i++) {
        if(students[i].score < min) min = students[i].score;
    }

    //check for max values
    for(int i = 0; i < 10; i++) {
        if(students[i].score > max) max = students[i].score;
    }

    //calculate sum
    for(int i = 0; i < 10; i++) {
        sum = sum + students[i].score;
    }

    //find average
    average = sum / 10.0;

    //print computations
    printf("%s", "min = ");
    printf("%d", min);
    printf("\n");
    printf("%s", "max = ");
    printf("%d", max);
    printf("\n");
    printf("%s", "average = ");
    printf("%f", average);
    printf("\n");
}

void deallocate(struct student* stud){
    /*Deallocate memory from stud*/
   free(stud);
}

int main(){
    struct student* stud = NULL;
    /*call allocate*/
    stud = allocate();
    /*call generate*/
    generate(stud);
    /*call output*/
    output(stud);
    /*call summary*/
    summary(stud);
    /*call deallocate*/
    printf("%s", "Q1");
    return 0;
}
