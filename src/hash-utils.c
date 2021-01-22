/* HASH UTILS.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:56:35 AM
 * Last edited:
 *   1/22/2021, 11:35:13 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains the hash-functions and manages the hash-table
**/

/************************************************
 * @file hash-utils.c
 * @author Nikolaus Rieder (hackxit@gmail.com)
 * @brief Hash-utilities is the main library for hash-table creation and manipulation.
 * @version 0.1
 * @date 2021-01-22
 * 
 * @copyright Copyright (c) 2021
 * 
 ***********************************************/

/*--- COMMON LIBRARIES ---*/
#define _GNU_SOURCE // for some reason this is necessary to use strlen()
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

/*--- CUSTOM LIBRARIES ---*/
#include "list-utils.h"
#include "file-utils.h"
#include "hash-utils.h"

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

table_t init_hashtable()
{
    // calloc sets the pointers to NULL by itself. Very handy.
    // table_t *table = malloc(sizeof(table_t *));
    // bucket_t **table = malloc(sizeof(bucket_t *));
    // if (table == NULL)
    // {
    //     fprintf(stderr, "Failed to allocate memory for hashtable!\n");
    //     return NULL;
    // }
    // table = calloc(TABLE_SIZE, sizeof(bucket_t *));
    table_t table = calloc(TABLE_SIZE, sizeof(bucket_t *));
    if (table == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for Table-Buckets!\n");
        return NULL;
    }
    return table;
}

table_t init_hashtable_from_file(const char *filename)
{
    table_t table = init_hashtable();
    FILE *f_input = fopen(filename, "r");
    if (f_input == NULL)
    {
        fprintf(stderr, "Error opening input-file %s for hashtable: %s", filename, strerror(errno));
        return NULL;
    }
    size_t len = 1; // Initial line-length, line is reallocated when it is longer
    // size_t is for storing bytes = unsigned long
    char *line = (char *)malloc(len * sizeof(char));
    ssize_t read; // signed size_t for including -1 (return value)
    if (line == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for line-buffer!\n");
        free(table);
        return NULL;
    }
    // NOTE the getline function automatically re-allocates the buffer
    // This happens when the line is longer than the given length
    // This re-allocation causes "possible" memory leak if not free'd properly
    // HELP: https://c-for-dummies.com/blog/?p=1112
    while ((read = getline(&line, &len, f_input)) != -1)
    {
        char *newLine = strchr(line, '\n'); // Get pointer to newline Character
        if (newLine != NULL)
        {
            *newLine = 0; // Set newline Character to Nullbyte => \0
        }
        char *tmp = strdup(line); // Duplicates string - figuring out the required allocation length itself.
        // NOTE Saving delimiters along with the word for more precise replacements
        // Hint: https://stackoverflow.com/questions/12460264/c-determining-which-delimiter-used-strtok (storing delims)
        // Hint: https://c-for-dummies.com/blog/?p=1690 (string duplication)
        char *word = strtok(line, " .;:,?\t");
        while (word != NULL)
        {
            char delimiters[2];
            delimiters[0] = tmp[word - line + strlen(word)]; // NOTE need to understand how this works
            delimiters[1] = tmp[word - line - 1];
            insert_word(table, word, delimiters);
            word = strtok(NULL, " .;:,?\t");
        }
        free(tmp); // necessary
    }
    free(line);
    close_file(f_input);
    return table;
}

unsigned int insert_word(table_t table, const char *word, const char *delimiters)
{
    unsigned int index = hash(word);
    if (table[index] == NULL) // first word with this hash
    {
        table[index] = create_bucket(word, delimiters);
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
            add_item_sorted(table[index], word, delimiters);
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

void select_bucket_to_print(table_t table)
{
    unsigned int selection = TABLE_SIZE + 1;
    char ch; // temp variable to flush stdin after scanf
    while (selection > TABLE_SIZE || selection < 1)
    {
        printf("Select bucket-number between 1 and " STRINGIFY(TABLE_SIZE) " to output: ");
        scanf("%u", &selection);
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }
    printf("Bucket[%u]: ", selection);
    print_bucket(table[selection - 1]);
    printf("\n");
}

void simple_bucket_selection(table_t table)
{
    bool selected_buckets[TABLE_SIZE] = {0};
    char selection[BUFSIZ] = {0}; // FIXME valgrind "Conditional jump or move depends on uninitialised value(s)"
    char *endptr;
    int bucket_num = 0;
    while (selection[0] != 'c')
    {
        printf("\nSelect bucket (1-" STRINGIFY(TABLE_SIZE) ") or exit (c): ");
        if (fgets(selection, sizeof(selection), stdin) != NULL)
        {
            bucket_num = (int)strtol(selection, &endptr, 10);
            if (selection[0] != '\n' && (*endptr == '\n' || *endptr == '\0'))
            {
                if (bucket_num > 0 && bucket_num <= TABLE_SIZE)
                {
                    printf("Bucket[%u]: ", bucket_num);
                    print_bucket(table[(bucket_num - 1)]);
                    printf("\n");
                    selected_buckets[(bucket_num - 1)] = true;
                }
            }
        }
    }
    printf("--- Your selected buckets ---\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (selected_buckets[i] == true)
        {
            printf("Bucket[%u]: ", (i + 1));
            print_bucket(table[i]);
            printf("\n");
        }
    }
}

void censor_bucket_selection(table_t table, const char *input_file, const char *output_file)
{
    bool selected_buckets[TABLE_SIZE] = {0};
    char selection[BUFSIZ] = {0}; // FIXME valgrind "Conditional jump or move depends on uninitialised value(s)"
    char *endptr;
    int bucket_num = 0;
    while (selection[0] != 'c')
    {
        printf("\nSelect bucket (1-" STRINGIFY(TABLE_SIZE) ") or exit (c): ");
        if (fgets(selection, sizeof(selection), stdin) != NULL)
        {
            bucket_num = (int)strtol(selection, &endptr, 10);
            if (selection[0] != '\n' && (*endptr == '\n' || *endptr == '\0'))
            {
                if (bucket_num > 0 && bucket_num <= TABLE_SIZE)
                {
                    print_bucket(table[(bucket_num - 1)]);
                    selected_buckets[(bucket_num - 1)] = true;
                }
            }
        }
    }
    copy_file(input_file, output_file); // Copy original contents of Input-File to Output-File
    printf("--- Your selected buckets for censoring---\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (selected_buckets[i] == true)
        {
            printf("Censoring...\n");
            printf("Bucket[%u]: ", (i + 1));
            print_bucket(table[i]);
            censor_bucket_in_file(output_file, table[i]);
            printf("\n");
        }
    }
}

void censor_file_with_bucket(table_t table, unsigned int bucket_num, const char *input_file, const char *output_file)
{
    if (bucket_num < TABLE_SIZE)
    {
        copy_file(input_file, output_file);
        printf("Censoring all words, contained in...");
        printf("Bucket[%u]: ", bucket_num);
        print_bucket(table[bucket_num]);
        if (censor_bucket_in_file(output_file, table[bucket_num]))
        {
            printf("Success!\n");
        }
        else
        {
            printf("Failed!\n");
        }
    }
    else
    {
        fprintf(stderr, "The bucket number is out of range!\n");
        return;
    }
}

void print_table(table_t table)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Bucket[%d]: ", i);
        print_bucket(table[i]);
        printf("\n");
    }
}

void print_selection(table_t table, unsigned int bucket_num)
{
    if (bucket_num < TABLE_SIZE)
    {
        printf("Printing selection...\n");
        printf("Bucket[%d]: ", bucket_num);
        print_bucket(table[bucket_num]);
    }
    else
    {
        fprintf(stderr, "The bucket number is out of range!\n");
        return;
    }
}

// void clear_file_with_bucket(table_t table, unsigned int bucket_num, const char *input_file, const char *output_file)
// {
//     if (bucket_num < TABLE_SIZE)
//     {
//         printf("Removing all words, which don't match...\n");
//         printf("Bucket[%u]: ", bucket_num);
//         print_bucket(table[bucket_num]);
//         if (clear_file_with_bucket(input_file, output_file, table[bucket_num]))
//         {
//             printf("Success!\n");
//         }
//         else
//         {
//             printf("Failed!\n");
//         }
//     }
//     else
//     {
//         fprintf(stderr, "The bucket number is out of range!\n");
//         return;
//     }
// }

void clean_table(table_t table)
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
    // free(table);
    free(table);
}