/* HASH UTILS.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:56:35 AM
 * Last edited:
 *   1/10/2021, 11:17:09 PM
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
#include <ctype.h>

/*--- CUSTOM LIBRARIES ---*/
#include "list-utils.h"

/*--- MACROS ---*/
// #define VERBOSE
#define TABLE_SIZE 43
#define MODIFIER 3
#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)

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

void select_bucket_to_print(bucket_t **table)
{
    unsigned int selection = TABLE_SIZE + 1;
    while (selection <= TABLE_SIZE && selection > 0)
    {
        printf("Select bucket-number between 1 and " STRINGIFY(TABLE_SIZE) " to output: ");
        scanf("%u", &selection);
    }
    printf("Bucket[%u]: ", selection);
    print_bucket(table[selection - 1]);
    printf("\n");
}

void bucket_selection(bucket_t **table)
{
    size_t *selected_buckets = malloc(sizeof(size_t));
    if (selected_buckets == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for bucket-selection!\n");
    }
    char selection[2];
    int bucket_num = 0;
    size_t counter = 0;
    while (selection[0] != 'c' && selection[1] != 'c')
    {
        printf("\nSelect bucket (1-" STRINGIFY(TABLE_SIZE) ") or continue (c): ");
        selection[0] = getc(stdin);
        selection[1] = getc(stdin);
        if (isdigit(selection[0]) && isdigit(selection[1]))
        {
            bucket_num = atoi(&selection[0]) + atoi(&selection[1]);
        }
        else if (isdigit(selection[0]))
        {
            bucket_num = atoi(&selection[0]);
        }
        else if (isdigit(selection[1]))
        {
            bucket_num = atoi(&selection[1]);
        }
        if (bucket_num > 0 && bucket_num <= TABLE_SIZE)
        {
            printf("Bucket[%u]: ", bucket_num);
            print_bucket(table[bucket_num - 1]);
            printf("\n");
            selected_buckets[counter] = bucket_num;
            bucket_num = 0;
            counter++;
            selected_buckets = realloc(selected_buckets, counter + 1);
            if (selected_buckets == NULL)
            {
                fprintf(stderr, "Failed to allocate memory for bucket-selection!\n");
            }
        }
    }
    printf("--- Your selected buckets ---\n");
    for (size_t i = 0; i < counter; i++)
    {
        printf("Bucket[%zu]: ", i);
        print_bucket(table[selected_buckets[i]]);
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