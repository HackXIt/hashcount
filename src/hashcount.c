/* HASHCOUNT.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:58:26 AM
 * Last edited:
 *   1/21/2021, 10:38:31 PM
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
#include <stdbool.h>

/*--- CUSTOM LIBRARIES ---*/
#include "hash-utils.h"

/*--- MACROS ---*/

void print_help();

int main(int argc, char *const argv[])
{
    bool interactive = false;
    char *filename_in = NULL;
    char *filename_out = NULL;
    char opt;
    while ((opt = getopt(argc, argv, "hf:o:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_help(argv[0]);
            return EXIT_SUCCESS;
            break;
        case 'b':
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
        case 'i':
            interactive = true;
            break;
        case '?':
            fprintf(stderr, "Invalid option '%c', use -h if you need help using this program.\n", optopt);
            return EXIT_FAILURE;
            break;
        default:
            fprintf(stderr, "There was an error: '%o'\n", opt);
            break;
        }
    }
    if (filename_in == NULL && argv[optind] != NULL)
    {
        filename_in = calloc(strlen(argv[optind]) + 1, sizeof(char));
        strcpy(filename_in, argv[optind]);
    }
    else if (filename_in == NULL && argv[optind] == NULL)
    {
        fprintf(stderr, "This program requires an input file!\nIt can be a text file or a pre-created binary by using option '-b'.");
        return EXIT_FAILURE;
    }
    if (filename_out != NULL)
    {
        if (strcmp(filename_in, filename_out) == 0)
        {
            fprintf(stderr, "This program is not capable of overwriting it's own input file.\n");
            return EXIT_FAILURE;
        }
    }
    // NOTE at the moment output-file is not required NOR implemented.
    table_t hashtable = init_hashtable_from_file(filename_in);
    if (interactive)
    {
        select_bucket_to_print(hashtable);
        simple_bucket_selection(hashtable);
    }
    else
    {
        print_table(hashtable);
        if (filename_out != NULL)
        {
            censor_bucket_selection(hashtable, filename_in, filename_out);
        }
    }
    clean_table(hashtable);
    if (filename_in != NULL)
    {
        free(filename_in);
    }
    if (filename_out != NULL)
    {
        free(filename_out);
    }
    return EXIT_SUCCESS;
}

void print_help(const char *argzero)
{
    printf("%s [OPTIONS]... [FILE]...\n", argzero);
    printf("Creates a hash-table, based on the words from the supplied file.\n");
    printf("The words are seperated by: \" .;:,?\\t\"\n\n");
    printf("---- ARGUMENTS:\t--------------------\n");
    printf("[FILE]\t\t text file to be parsed by the program for the hash-table.\n");
    printf("---- OPTIONS:\t--------------------\n");
    printf("\t -h \t\t prints this help text.");
    printf("\t -b [FILENAME]\t binary file that will be parsed to generate the table.\n");
    printf("\t -o [FILENAME]\t name of the binary file, in which the hash-table will be stored.\n");
    printf("\t -i \t\t runs the program in interactive-mode, requiring user-input for the program to run.\n");
    printf("\n");
}