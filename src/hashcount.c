/* HASHCOUNT.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:58:26 AM
 * Last edited:
 *   1/8/2021, 1:54:39 AM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains the main and tests the project libraries
 *   It's also responsible for handling arguments.
**/

// TODO delete unnecessary common libraries, if they are not used in this file

/*--- COMMON LIBRARIES ---*/
#include <stdlib.h>
#include <stdio.h>
// #include <stdbool.h>
#include <string.h>
#include <getopt.h>

/*--- CUSTOM LIBRARIES ---*/
#include "hash-utils.h"

/*--- MACROS ---*/

void print_help();

int main(int argc, char const *argv[])
{
    char *filename_in = NULL;
    char *filename_out = NULL;
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
    // As of now output is not required.
    if (filename_in == NULL)
    {
        fprintf(stderr, "Please provide an input-filename.\n");
        return EXIT_FAILURE;
    }
    else
    {
        FILE F_in = fopen(filename_in, "r");
    }
    char *line = NULL;
    size_t len = 0; // size_t is for storing bytes = unsigned long
    ssize_t read;   // signed size_t for including -1 (return value)
    bucket_t **hashtable = init_hashtable();
    if (hashtable == NULL)
    {
        fprintf(stderr, "Couldn't create hashtable!\n");
        return EXIT_FAILURE
    }
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