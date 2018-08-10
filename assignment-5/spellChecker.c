#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

int levenshtein(char *s1, char *s2) {
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return(column[s1len]);
}

void addLevenshteinValues(HashMap * map, char * s1) {
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            while (link != NULL)
            {
                link->value = levenshtein(link->key, s1);
                link = link->next;
            }
        }
    }
}

void printBucketAtIndex(HashMap * map, int index) {
    HashLink* link = map->table[index];
    if (link != NULL)
    {
        printf("\nBucket %i ->", index);
        while (link != NULL)
        {
            printf(" (%s, %d) ->", link->key, link->value);
            link = link->next;
        }
    }
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement
  char * temp = nextWord(file);

    while(temp != NULL) {
        hashMapPut(map, temp, 1);
        temp = nextWord(file);
    }
    hashMapPrint(map);
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
/* function to swap data of two nodes a and b*/
void swap(struct HashLink *a, struct HashLink *b)
{
    int temp = a->value;
    a->value = b->value;
    b->value = temp;
}
//BUBBLE SORT FROM geeksforgeeks.org
void bubbleSort(struct HashLink *start)
{
    int swapped, i;
    struct HashLink *ptr1;
    struct HashLink *lptr = NULL;

    /* Checking for empty list */
    if (ptr1 == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->value > ptr1->next->value)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);

        //FIXME: Implement
        if(hashMapContainsKey(map, inputBuffer) != 1) {
            addLevenshteinValues(map, inputBuffer);

            /* GET MATCHES BASED ON HASH FUNCTION

            int hashIndex = HASH_FUNCTION(inputBuffer);

            //Sort the bucket using bubble sort
            struct HashLink * bucketStart = map->table[hashIndex];
            bubbleSort(bucketStart);

            struct HashLink * bucketStartAfterSort = map->table[hashIndex];
            printBucketAtIndex(map, hashIndex);

            //Print the first 5 values
            printf("%s", "\nDid you mean?\n");
            for(int i = 0; i < 5; i++) {
                printf("%s \n", bucketStartAfterSort->key);
                bucketStartAfterSort = bucketStartAfterSort->next;
            }
             */
            int wordCounter = 0;
            int levenshteinCounter = 1;
            printf("%s\n", "Did you mean?");
            while(wordCounter < 5) {
                for(int i = 0; i < map->capacity; i++) {
                    struct HashLink * temp = map->table[i];
                    while(temp != NULL && wordCounter < 5) {
                        if(temp->value == levenshteinCounter) {
                            printf("%s \n", temp->key);
                            wordCounter++;
                        }
                        temp = temp->next;
                    }
                }
                levenshteinCounter++;
            }



        }
        else {
            printf("%s\n", "Word spelled correctly.");
        }

        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    
    hashMapDelete(map);
    return 0;
}