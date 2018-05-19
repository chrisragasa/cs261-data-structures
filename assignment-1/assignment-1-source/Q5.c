/* CS261- Assignment 1 - Q5 */
/* Name: Christopher Ragasa
 * Date: 1/22/18
 * Solution description:
   Create a program that modifies a word to appear with "stick caps". For
   example, if the user enters, "sticky", the program should print, "StIcKy".
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/

    //store count of characters
    int characterCount = 0;
    for(int i = 0; word[i] != '\0'; i++) {
        characterCount++;
    }

    //loop to convert characters of word
    for(int i = 0; i < characterCount; i++) {
        if(i % 2 == 0) {
            if(word[i] >= 'a' && word[i] <= 'z') { //convert to uppercase, if currently lowercase
                word[i] = toUpperCase(word[i]);
            }
        }
        if(i % 2 == 1) {
            if(word[i] >= 'A' && word[i] <= 'Z') { //convert to lowercase, if currently uppercase
                word[i] = toLowerCase(word[i]);
            }
        }
    }
}

int main(){
    /*Read word from the keyboard using scanf*/
    char inputWord[20];
    char * ptrWord;
    ptrWord = inputWord;
    printf("%s", "Please enter a word with less than 20 characters.");
    scanf("%s", inputWord);

    /*Call sticky*/
    sticky(ptrWord);

    /*Print the new word*/
    printf("%s", inputWord);

   return 0;
}
