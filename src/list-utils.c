/* LIST UTILS.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:57:22 AM
 * Last edited:
 *   1/8/2021, 2:23:12 AM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains the list definitions and list functions, which
 *   supports the hash-table in case of collisions.
**/

// TODO delete unnecessary common librarie, if they are not used in this file

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

/*--- DEFINITIONS ---*/

/*
I need a function which creates a new item for the bucket.
*/
item_t *create_item(const char *word)
{
    item_t *newItem = malloc(sizeof(item_t));
    if (newItem == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for new Item!\n");
        return NULL;
    }
    newItem->word = malloc(sizeof(char) * strlen(word) + 1);
    newItem->count = 1;
    newItem->node.next = NULL;
    newItem->node.prev = NULL;
    if (newItem->word == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for Item-Word!\n");
        free(newItem); // Clearing memory on potential failures: Bonus Points?
        return NULL;
    }
    strcpy(newItem->word, word);
    return newItem;
}

/*
I need a function which creates a bucket with an initializing word.
*/
bucket_t *create_bucket(const char *word)
{
    bucket_t *newBucket = malloc(sizeof(bucket_t));
    if (newBucket == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for new Bucket!\n");
        return NULL;
    }
    newBucket->start = create_item(word);
    if (newBucket->start == NULL)
    {
        fprintf(stderr, "Cannot create bucket, because item-creation failed!\n");
        free(newBucket);
        return NULL;
    }
    newBucket->end = newBucket->start;
    return newBucket;
}

/*
This function assumes uniqueness of the new item.
The user needs to check if the item already exists or not.
*/
void append_item(bucket_t *bucket, const char *word)
{
    item_t *newItem = create_item(word);
    bucket->end->node.next = newItem;
    newItem->node.prev = bucket->end;
    bucket->end = newItem;
    sort_bucket(bucket);
}

/*
I need a function which adds an item AND keeps the list sorted.
*/
// void add_item_sorted(bucket_t *bucket, const char *word)
// {
// }

void swap_items(item_t *itemA, item_t *itemB)
{
    item_t temp = {
        .word = itemA->word,
        .count = itemA->count
        // Ignoring nodes, since they won't need to be swapped.
    };
    strcpy(itemA->word, itemB->word);
    itemA->count = itemB->count;
    strcpy(itemB->word, temp.word);
    itemB->count = temp.count;
}

/*
I need a search function for the bucket, which returns the instance, 
in order to increase the counter.
Or it returns NULL if the word is not in the bucket.
If it is NULL I can attach it to the end of the LIST.
*/
item_t *search_bucket(const bucket_t *bucket, const char *word)
{
    item_t *instance = bucket->start;
    while (instance != NULL)
    {
        if (strcmp(instance->word, word) == 0) // This comparison is more readable than negation.
        {
            return instance; // Word already exists in BucketList
        }
        instance = instance->node.next;
    }
    return NULL;
}

/*
I need a function which sorts the list alphabetically.
What algorithm should I use for this?
*/
void sort_bucket(bucket_t *bucket)
{
    // FIXME This sort shits and stinks!
    item_t *instance = bucket->start;
    item_t *next = instance->node.next;
    while (instance != NULL)
    {
        while (next != NULL)
        {
            // sort ignoring upper- & lowercase
            // Uppercase will always be lower than lowercase
            if (strcmp(instance->word, next->word) < 0) // if str2 is lower than str1
            {
                swap_items(instance, next);
            }
            next = next->node.next;
        }
        instance = instance->node.next;
    }
    return;
}

/*
I need a function which prints the contents of a bucket.
The function should print the bucket regardless if it's empty, starting or full.
*/
void print_bucket(const bucket_t *bucket)
{
    if (bucket == NULL)
    { // No words in bucket
        printf("-EMPTY-");
        return;
    }
    item_t *instance = bucket->start;
    // Print first word
    printf("%s", instance->word);
    if (instance->count > 1)
    {
        printf("(%zu)", instance->count);
    }
    if (bucket->start == bucket->end) // Single word in bucket
    {
        return;
    }
    // Print the rest
    while (instance != NULL && instance != bucket->end) // Multiple words in bucket
    {
        instance = instance->node.next;
        printf(", %s", instance->word);
        if (instance->count > 1)
        {
            printf("(%zu)", instance->count);
        }
    }
    return;
}

/*
I need a function which free's the allocated memory in a bucket.
*/
void clean_bucket(bucket_t *bucket)
{
    item_t *instance = NULL;
    while (bucket->start != NULL)
    {
        instance = bucket->start->node.next;
        free(bucket->start->word);
        free(bucket->start);
        bucket->start = instance;
    }
}