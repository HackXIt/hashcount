/* HASHCOUNT.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:58:26 AM
 * Last edited:
 *   1/10/2021, 8:12:34 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains the main and tests the project libraries
 *   It's also responsible for handling arguments.
**/

// TODO delete unnecessary common libraries, if they are not used in this file

/*--- COMMON LIBRARIES ---*/
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
// #include <stdbool.h>
#include <string.h>
#include <getopt.h>

/*--- CUSTOM LIBRARIES ---*/
// FIXME I don't want to import list-utils here
// But it's throwing unknown type bucket_t, so ???
#include "list-utils.h"
#include "hash-utils.h"

/*--- MACROS ---*/

void print_help();

int main(int argc, char *const argv[])
{
    char *filename_in = NULL;
    char *filename_out = NULL;
    char opt;
    while ((opt = getopt(argc, argv, "hf:o:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_help(argv[0]);
            break;
        case 'f':
            filename_in = calloc(strlen(optarg) + 1, sizeof(char));
            if (filename_in == NULL)
            {
                fprintf(stderr, "Failed to allocate memory for filename_in!\n");
                return EXIT_FAILURE;
            }
            strcpy(filename_in, optarg);
            break;
        case 'o':
            filename_out = calloc(strlen(optarg) + 1, sizeof(char));
            if (filename_out == NULL)
            {
                fprintf(stderr, "Failed to allocate memory for filename_in!\n");
                return EXIT_FAILURE;
            }
            strcpy(filename_out, optarg);
            break;
        case '?':
            fprintf(stderr, "Invalid option '%c', use -h if you need help using this program.\n", optopt);
            break;
        default:
            fprintf(stderr, "There was an error: '%o'\n", opt);
            break;
        }
    }
    // NOTE at the moment output-file is not required NOR implemented.
    FILE *F_in = NULL;
    if (filename_in == NULL)
    {
        fprintf(stderr, "Please provide an input-filename.\n");
        return EXIT_FAILURE;
    }
    else
    {
        F_in = fopen(filename_in, "r");
    }
    size_t len = 1; // Initial line-length, line is reallocated when it is longer
    // size_t is for storing bytes = unsigned long
    char *line = (char *)malloc(len * sizeof(char));
    if (line == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for line in text!\n");
    }
    ssize_t read; // signed size_t for including -1 (return value)
    bucket_t **hashtable = init_hashtable();
    if (hashtable == NULL)
    {
        fprintf(stderr, "Couldn't create hashtable!\n");
        return EXIT_FAILURE;
    }
    // NOTE the getline function automatically re-allocates the buffer
    // This happens when the line is longer than the given length
    // This re-allocation causes "possible" memory leak if not free'd properly
    // HELP: https://c-for-dummies.com/blog/?p=1112
    while ((read = getline(&line, &len, F_in)) != -1)
    {
        char *newLine = strchr(line, '\n'); // Get pointer to newline Character
        if (newLine != NULL)
        {
            *newLine = 0; // Set newline Character to Nullbyte => \0
        }
        char *word = strtok(line, " .;:,?\t");
        while (word != NULL)
        {
            insert_word(hashtable, word);
            word = strtok(NULL, " .;:,?\t");
        }
    }
    print_table(hashtable);
    clean_table(hashtable);
    free(filename_in);
    free(filename_out);
    free(line);
    fclose(F_in);
    return EXIT_SUCCESS;
}

void print_help(const char *argzero)
{
    printf("%s [OPTIONS]... [WORDS]...\n", argzero);
    printf("Creates a hash-table, based on the words from the supplied file.\n");
    printf("The words are seperated by: \".;:,?\\t\"\n\n");
    printf("---- OPTIONS:\t--------------------\n");
    printf("\t -h \t\t prints this help text.");
    printf("\t -f [FILE]\t text or binary file that will be parsed to generate the table.\n");
    printf("\t -o [FILENAME]\t name of the binary file, in which the hash-table will be stored.\n");
    printf("\n");
}