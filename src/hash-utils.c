/* HASH UTILS.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:56:35 AM
 * Last edited:
 *   1/10/2021, 9:13:22 PM
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
            /* Add new Item */
            add_item_sorted(table[index], word);
            /* To work with unsorted list (faster but unsorted) */
            // append_item(table[index], word);
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