#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

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
//FIXME:: Do the necessary change to make the implementation //case-insensitive
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
            // .............
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

    //Convert string to lowercase
    for (int i=0; word[i]; i++)
        word[i] = tolower((unsigned char)word[i]);

    return word;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    //FIXME: Concordance code begins here ---
    // Be sure to free the word after you are done with it here.

    FILE * file = fopen(fileName, "r");
    char * currentWord = nextWord(file);
    while(currentWord != NULL) {
        //Check if the word already exists in the hashmap
        //If it does, grab it's value and increment it by one when adding to the hashmap
        if(hashMapContainsKey(map, currentWord)) {
            int * count = hashMapGet(map, currentWord);
            hashMapPut(map, currentWord, *count + 1);
        }
            //Otherwise, add it to the hash map as a first occurance
        else {
            hashMapPut(map,currentWord, 1);
        }
        currentWord = nextWord(file);
    }

    //Print all of the key/value pairs in the map
    for(int i = 0; i < map->capacity; i++) {
        struct HashLink * current = map->table[i];
        while(current != NULL) {
            printf("%s: ", current->key);
            printf("%d \n", current->value);
            current = current->next;
        }
    }

    // --- Concordance code ends here ---
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}