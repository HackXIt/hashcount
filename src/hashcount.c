/* HASHCOUNT.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:58:26 AM
 * Last edited:
 *   1/22/2021, 11:53:33 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains the main and tests the project libraries
 *   It's also responsible for handling arguments.
**/

/************************************************
 * @file hashcount.c
 * @author Nikolaus Rieder (hackxit@gmail.com)
 * @brief Hashcount is the main program, responsible for CLI-handling and general usage.
 * @version 0.1
 * @date 2021-01-22
 * 
 * @copyright Copyright (c) 2021
 * 
 ***********************************************/

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
// char *get_filename(char *message);
// const char *get_filename_ext(const char *filename);
// bool interactive_mode(table_t table);
char *allocate_filename(char *filename, char *error_message);
void clear_filenames(char *a, char *b, char *c, char *d);

int main(int argc, char *const argv[])
{
    // bool interactive = false;
    bool censor = false;
    bool keep = false;
    bool selection = false;
    char *filename_in = NULL;
    char *filename_out = NULL;
    char *filename_bin = NULL;
    char *filename_new = NULL;
    unsigned int bucket = 0;
    char opt;
    table_t hashtable;
    /* ---- ARGUMENT-Handling ---- */
    while ((opt = getopt(argc, argv, "hib:n:o:c:k:p:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_help(argv[0]);
            return EXIT_SUCCESS;
            break;
        // case 'i':
        //     interactive = true;
        //     break;
        // case 'b':
        //     filename_bin = allocate_filename(optarg, "Failed to allocate memory for filename_bin!\n");
        //     break;
        // case 'n':
        //     filename_new = allocate_filename(optarg, "Failed to allocate memory for filename_new!\n");
        //     break;
        case 'o':
            filename_out = allocate_filename(optarg, "Failed to allocate memory for filename_out!\n");
            break;
        case 'c':
            censor = true;
            bucket = strtoul(optarg, NULL, 10);
            break;
        // case 'k':
        //     keep = true;
        //     bucket = strtoul(optarg, NULL, 10);
        case 'p':
            selection = true;
            bucket = strtoul(optarg, NULL, 10);
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
    /* ---- Interactive-Mode ---- */
    // if (interactive)
    // {
    //     clear_filenames(filename_in, filename_out, filename_new, filename_bin);
    //     filename_in = get_filename("Bitte geben Sie den Namen der Input-Datei ein:");
    //     hashtable = init_hashtable_from_file(filename_in);
    //     interactive_mode(hashtable);
    //     clean_table(hashtable);
    //     return EXIT_SUCCESS;
    // }
    /* ---- ERROR-Handling ---- */
    if (filename_in == NULL && argv[optind] != NULL)
    {
        filename_in = allocate_filename(argv[optind], "Failed to allocate memory for filename_in!\n");
    }
    else if (filename_in == NULL && argv[optind] == NULL)
    {
        fprintf(stderr, "This program requires an input file!\nStart program with option -h for execution parameters.\n");
        return EXIT_FAILURE;
    }
    if ((censor || keep) && filename_out == NULL)
    {
        fprintf(stderr, "To censor/remove words from an input file, an output file \"-o [FILE.txt]\" is required.\n");
        clear_filenames(filename_in, filename_out, filename_new, filename_bin);
        return EXIT_FAILURE;
    }
    if (filename_out != NULL)
    {
        if (strcmp(filename_in, filename_out) == 0)
        {
            fprintf(stderr, "This program is not capable of overwriting it's own input file.\n");
            clear_filenames(filename_in, filename_out, filename_new, filename_bin);
            return EXIT_FAILURE;
        }
    }
    if (censor && keep)
    {
        fprintf(stderr, "It is not possible to censor and remove at the same time.\n");
        clear_filenames(filename_in, filename_out, filename_new, filename_bin);
        return EXIT_FAILURE;
    }
    // if (filename_bin != NULL)
    // {
    //     hashtable = init_hashtable_from_binary(filename_bin); // TODO
    // }
    // else
    // {
    hashtable = init_hashtable_from_file(filename_in);
    // }
    if (censor)
    {
        censor_file_with_bucket(hashtable, bucket, filename_in, filename_out);
    }
    // if (keep)
    // {
    //     clear_file_with_bucket(hashtable, bucket, filename_in, filename_out); // TODO
    // }
    if (selection)
    {
        print_selection(hashtable, bucket); // TODO
    }
    if (!censor && !keep && !selection)
    {
        print_table(hashtable);
    }
    clean_table(hashtable);
    clear_filenames(filename_in, filename_out, filename_new, filename_bin);
    return EXIT_SUCCESS;
}

void print_help(const char *argzero)
{
    /*
    Possible Options:
    h - help
    b - binary
    n - new
    o - output
    c - censor
    k - keep
    p - print
    i - interactive
    */
    printf("%s [OPTIONS]... [FILE.txt]...\n", argzero);
    printf("Creates a hash-table, based on the words from the supplied file.\n");
    printf("The words are seperated by: \" .;:,?\\t\"\n\n");
    printf("---- ARGUMENTS:\t--------------------\n");
    printf("[FILE.txt]\t\t text file to be parsed by the program for the hash-table.\n");
    printf("---- OPTIONS:\t--------------------\n");
    printf("\t -h \t\t prints this help text.");
    printf("\t -b [FILE.bin]\t binary file that will be parsed and appended into if the user wants this. (not implemented yet)\n");
    printf("\t -n [FILE.bin]\t New binary file to be created and filled with the hashtable. (not implemented yet)\n");
    printf("\t -o [FILE.txt]\t name of the output file, to which the censor/remove changes will be written.\n");
    printf("\t -c [number]\t censor the words in Bucket[num] from the input-file and write result to the output-file.\n\t\t\t(Requires option '-o')\n");
    printf("\t -k [number]\t keep the words in Bucket[num] from the input-file and remove all other words. Write result to the output-file. (not implemented yet)\n\t\t\t(Requires option '-o')\n");
    printf("\t -p [number]\t only print the given bucket-number instead of the whole table.\n");
    printf("\t -i \t\t runs the program in interactive-mode, requiring user-input for the program to run. (not implemented yet)\n(This will ignore all other options & parameters)\n");
    printf("\n");
}

/************************************************
 * @brief Dynamically allocate memory for a file-name.
 * 
 * This function allocates memory for the given filename.
 * If the allocation fails, the provided error message is printed.
 * 
 * @param filename the string which contains the filename to be allocated.
 * @param error_message the error message to be printed to stderr if allocation fails.
 * @return char* returns pointer to the allocated filename.
 ***********************************************/
char *allocate_filename(char *filename, char *error_message)
{
    char *newFilename = calloc(strlen(filename) + 1, sizeof(char));
    if (newFilename == NULL)
    {
        fprintf(stderr, error_message);
        return NULL;
    }
    strcpy(newFilename, filename);
    return newFilename;
}

/************************************************
 * @brief Read the filename from stdin.
 * 
 * @param message the message to be printed before asking for user-input.
 * @return char* returns the filename that was read from stdin.
 ***********************************************/
// char *get_filename(char *message)
// {
//     char *filename;
//     printf("%s", message);
//     scanf("%s", filename);

//     return filename;
// }

// const char *get_filename_ext(const char *filename)
// {
//     const char *dot = strrchr(filename, '.');
//     if (!dot || dot == filename)
//     {
//         return "";
//     }
//     return dot + 1;
// }

// bool interactive_mode(table_t table)
// {
// }

/************************************************
 * @brief Clears dynamically allocated memory of the filenames from main. 
 * 
 * The function checks each parameter against NULL and free's the memory if it's not NULL.
 * If no filename was allocated, then this function does nothing.
 * 
 * @param a filename_a
 * @param b filename_b
 * @param c filename_c
 * @param d filename_d
 ***********************************************/
void clear_filenames(char *a, char *b, char *c, char *d)
{
    if (a != NULL)
    {
        free(a);
    }
    if (b != NULL)
    {
        free(b);
    }
    if (c != NULL)
    {
        free(c);
    }
    if (d != NULL)
    {
        free(d);
    }
}