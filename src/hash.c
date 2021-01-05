/* HASH.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:56:35 AM
 * Last edited:
 *   1/5/2021, 8:52:00 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This files contains the hash-functions and manages the hash-table
**/

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define DEBUG
// #define VERBOSE
#define TABLE_SIZE 50
#define MODIFIER 3

struct nodes
{
    struct BucketItem *next;
    struct BucketItem *prev;
};

typedef struct BucketItem
{
    char *word;
    size_t count;
    struct nodes node;
} item_t;

typedef struct Bucket
{
    item_t *start;
    item_t *end;
} bucket_t;

unsigned int hash(const char *word)
{
    int length = strlen(word);
    unsigned int hash_value = 0;
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
        hash_value = hash_value % TABLE_SIZE;
    }
#ifdef VERBOSE
    printf("%u <= %s\n", hash_value, word);
#endif
    return hash_value;
}

bucket_t **init_hashtable()
{
    bucket_t **table = malloc(sizeof(bucket_t) * TABLE_SIZE);
    if (table != NULL)
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            table[i] = NULL;
        }
    }
    else
    {
        fprintf(stderr, "Failed to allocate memory!");
        return NULL;
    }

    return table;
}
item_t *create_bucket(const char *word)
{
    item_t *newBucket = malloc(sizeof(item_t));
    if (newBucket != NULL)
    {
        newBucket->word = malloc(sizeof(char) * strlen(word) + 1);
        newBucket->count = 1;
        if (newBucket->word != NULL)
        {
            strcpy(newBucket->word, word);
        }
        else
        {
            fprintf(stderr, "Failed to allocate memory for Bucket-Word!\n");
            free(newBucket);
            return NULL;
        }
        newBucket->node.next = NULL;
        newBucket->node.prev = NULL;
    }
    else
    {
        fprintf(stderr, "Failed to allocate memory for new Bucket!\n");
        return NULL;
    }
    return newBucket;
}
bool insert_word(bucket_t **table, const char *word)
{
    unsigned int index = hash(word);
    if (table[index] == NULL)
    {
        table[index] = malloc(sizeof(bucket_t));
        if (table[index] != NULL)
        {
            table[index]->start = create_bucket(word);
            if (table[index]->start != NULL)
            {
                table[index]->end = table[index]->start;
            }
            else
            {
                return false;
            }
        }
    }
    else // hash-collision occured
    {
        /* Check Bucket if word already exists*/
        item_t *instance = table[index]->start;
        while (instance != NULL)
        {
            if (!(strcmp(instance->word, word)))
            { // Negated because strcmp returns 0 if equal
                instance->count++;
                return true; // Word already exists in BucketList
            }
            instance = instance->node.next;
        }
        /* Create new Bucket */
        item_t *newCollision = create_bucket(word);
        table[index]->end->node.next = newCollision;
        newCollision->node.prev = table[index]->end;
        table[index]->end = newCollision;
    }
    return true;
}

void print_table(bucket_t **table)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Bucket[%d]: ", i);
        if (table[i]->start == NULL)
        {
            printf("-EMPTY-\n");
            continue;
        }
        else if (table[i]->start == table[i]->end)
        {
            printf("%s", table[i]->end->word);
            if (table[i]->end->count > 1)
            {
                printf("(%zu)", table[i]->end->count);
            }
        }
        else
        {
            printf("%s", table[i]->start->word);
            if (table[i]->start->count > 1)
            {
                printf("(%zu)", table[i]->start->count);
            }
            item_t *instance = table[i]->start->node.next;
            while (instance != NULL)
            {
                printf(", %s", instance->word);
                if (instance->count > 1)
                {
                    printf("(%zu)", instance->count);
                }
                instance = instance->node.next;
            }
        }
        printf("\n");
    }
}

void cleanup(bucket_t **table)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        item_t *tmp = table[i]->start;
        while (table[i]->start != NULL)
        {
            tmp = table[i]->start->node.next;
            free(table[i]->start->word);
            free(table[i]->start);
            table[i]->start = tmp;
        }
        free(table[i]);
    }
    free(table);
}

#ifdef DEBUG
int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "Missing file argument.\n");
        return EXIT_FAILURE;
    }
    FILE *f_ptr = fopen(argv[1], "r");
    if (f_ptr == NULL)
    {
        fprintf(stderr, "Invalid File-Pointer.\n");
        return EXIT_FAILURE;
    }
    char *line = NULL;
    size_t len = 0; // size_t is for storing bytes = unsigned long
    ssize_t read;   // signed size_t for including -1 (return value)
    bucket_t **hashtable = init_hashtable();
    while ((read = getline(&line, &len, f_ptr)) != -1)
    {
        char *newLine = strchr(line, '\n'); // Get pointer to newline Character
        if (newLine != NULL)
        {
            *newLine = 0; // Set newline Character to Nullbyte => \0
        }
        char *word = strtok(line, " .");
        while (word != NULL)
        {
            insert_word(hashtable, word);
            word = strtok(NULL, " ");
        }
    }
    print_table(hashtable);
    cleanup(hashtable);
    fclose(f_ptr);
    return EXIT_SUCCESS;
}

#endif