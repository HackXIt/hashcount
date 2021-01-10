/* HASH UTILS.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:56:35 AM
 * Last edited:
 *   1/10/2021, 9:07:53 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This files contains the hash-functions and manages the hash-table
**/

/*--- COMMON LIBRARIES ---*/
#define _GNU_SOURCE // for some reason this is necessary to use strlen()
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*--- CUSTOM LIBRARIES ---*/
#include "list-utils.h"

/*--- MACROS ---*/
// #define VERBOSE
#define TABLE_SIZE 43
#define MODIFIER 3

unsigned int hash(const char *word)
{
    int length = strlen(word);
    size_t hash_value = 0;
    for (int i = 0; i < length - 1; i++)
    {
        if (i % 2)
        {
            hash_value += word[i];
        }
        else
        {
            hash_value += word[i] * MODIFIER;
        }
    }
    hash_value = hash_value % TABLE_SIZE;
#ifdef VERBOSE
    printf("%zu <= %s (%zu)\n", hash_value, word, strlen(word));
#endif
    return hash_value;
}

bucket_t **init_hashtable()
{
    // calloc sets the pointers to NULL by itself. Very handy.
    bucket_t **table = calloc(TABLE_SIZE, sizeof(bucket_t *));
    if (table == NULL)
    {
        fprintf(stderr, "Failed to allocate memory!");
        return NULL;
    }
    return table;
}

bool insert_word(bucket_t **table, const char *word)
{
    unsigned int index = hash(word);
    if (table[index] == NULL) // first word with this hash
    {
        table[index] = create_bucket(word);
        if (table[index] == NULL)
        {
            fprintf(stderr, "Cannot insert word in hash-table because bucket-creation failed!\n");
            return false;
        }
    }
    else // hash-collision occured
    {
        /* Check Bucket if word already exists*/
        item_t *instance = search_bucket(table[index], word);
        if (instance == NULL)
        {
            /* Append new Item */
            add_item_sorted(table[index], word);
        }
        else
        {
            instance->count++;
        }
    }
    return true;
}

void print_table(bucket_t **table)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Bucket[%d]: ", i);
        print_bucket(table[i]);
        printf("\n");
    }
}

void clean_table(bucket_t **table)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i] == NULL)
        {
            free(table[i]);
            continue;
        }
        else
        {
            clean_bucket(table[i]);
        }
        free(table[i]);
    }
    free(table);
}

// int main(int argc, char const *argv[])
// {
//     if (argc == 1)
//     {
//         fprintf(stderr, "Missing file argument.\n");
//         return EXIT_FAILURE;
//     }
//     FILE *f_ptr = fopen(argv[1], "r");
//     if (f_ptr == NULL)
//     {
//         fprintf(stderr, "Invalid File-Pointer.\n");
//         return EXIT_FAILURE;
//     }
//     char *line = NULL;
//     size_t len = 0; // size_t is for storing bytes = unsigned long
//     ssize_t read;   // signed size_t for including -1 (return value)
//     bucket_t **hashtable = init_hashtable();
//     while ((read = getline(&line, &len, f_ptr)) != -1)
//     {
//         char *newLine = strchr(line, '\n'); // Get pointer to newline Character
//         if (newLine != NULL)
//         {
//             *newLine = 0; // Set newline Character to Nullbyte => \0
//         }
//         char *word = strtok(line, " .;:,?\t");
//         while (word != NULL)
//         {
//             insert_word(hashtable, word);
//             word = strtok(NULL, " .;:,?\t");
//         }
//     }
//     print_table(hashtable);
//     clean_table(hashtable);
//     fclose(f_ptr);
//     return EXIT_SUCCESS;
// }