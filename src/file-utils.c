/* FILE UTILS.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:51:22 AM
 * Last edited:
 *   1/22/2021, 11:28:05 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains all file-utility functions
**/

/************************************************
 * @file file-utils.c
 * @author Nikolaus Rieder (hackxit@gmail.com)
 * @brief File utilities is an internal library for file-related operations.
 * @version 0.1
 * @date 2021-01-22
 * 
 * @copyright Copyright (c) 2021
 * 
 ***********************************************/

/*--- COMMON LIBRARIES ---*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*--- CUSTOM LIBRARIES ---*/
#include "list-utils.h"

/*--- MACROS ---*/

/* TODO Function-Pointer improvement
I need a function which reads a line from the FILE-Stream,
and inserts it into the hashtable, by using the supplied function-pointer.
*/

void close_file(FILE *file)
{
    if (fclose(file) != 0)
    {
        fprintf(stderr, "Error when trying to close file.\n");
    }
}

unsigned int copy_file(const char *filename_in, const char *filename_out)
{
    FILE *file_in = fopen(filename_in, "r");
    FILE *file_out = fopen(filename_out, "w");
    if (file_in == NULL)
    {
        fprintf(stderr, "Error opening input-file \"%s\" for copying: %s\n", filename_in, strerror(errno));
        return false;
    }
    if (file_out == NULL)
    {
        fprintf(stderr, "Error opening output-file \"%s\" for copying: %s\n", filename_out, strerror(errno));
        close_file(file_in);
        return false;
    }
    char ch;
    while ((ch = fgetc(file_in)) != EOF)
    {
        fputc(ch, file_out);
    }
    close_file(file_in);
    close_file(file_out);
    return true;
}

/* NOTE Function-Pointer improvement
    Once I used copy-paste to re-use the below censor-algorithm from submission 11, I thought to myself:
    A function which reads the input-file and executes another function would be great for this.
    That would be a nice usage for function-pointers to learn... but oh hey 27 hours until deadline, I don't have time for this.
    So let's just keep that as a note for potential future iterations.
    */
unsigned int censor_bucket_in_file(const char *filename, const bucket_t *bucket)
{
    FILE *to_censor = fopen(filename, "r+");
    if (to_censor == NULL)
    {
        fprintf(stderr, "Error opening file \"%s\" to be censored: %s\n", filename, strerror(errno));
        return false;
    }
    item_t *instance = bucket->start;
    char dump[BUFSIZ];
    char *censor_sub = NULL;
    unsigned int censor_count = 0;
    fpos_t prev_pos;
    fgetpos(to_censor, &prev_pos);
    /* WORD-CENSORING */
    while (fgets(dump, BUFSIZ, to_censor) != NULL)
    {
        while (instance != NULL)
        {
            size_t len = strlen(instance->word);
            while ((censor_sub = strstr(dump, instance->word_with_delimiters)) != NULL)
            {
                memset(censor_sub + 1, '*', len);
                censor_count++;
            }
            instance = instance->node.next;
        }
        if (fsetpos(to_censor, &prev_pos) == 0)
        {
            fputs(dump, to_censor);
            fflush(to_censor);
        }
        fgetpos(to_censor, &prev_pos);
        instance = bucket->start;
    }
    close_file(to_censor);
    printf("%u occurences of %zu Bucket-words were censored in %s\n", censor_count, bucket->wordcount, filename);
    return true;
}

// unsigned int clear_file_with_bucket(const char *input_file, const char *output_file, const bucket_t *bucket)
// {
//     FILE *f_in = fopen(input_file, "r");
//     if (f_in == NULL)
//     {
//         fprintf(stderr, "Error opening input-file \"%s\" for reading: %s\n", filename, strerror(errno));
//     }
//     FILE *f_out = fopen(filename, "w");
//     if (f_out == NULL)
//     {
//         fprintf(stderr, "Error opening output-file \"%s\" for writing: %s\n", filename, strerror(errno));
//         return false;
//     }
//     item_t *instance = bucket->start;
//     char dump[BUFSIZ];
//     unsigned int clear_count = 0;
//     char *word;
//     /* WORD-CENSORING */
//     while (fgets(dump, BUFSIZ, f_in) != NULL)
//     {
//         while (instance != NULL)
//         {

//         }
//         instance = bucket->start;
//     }
//     close_file(to_clear);
//     printf("%u occurences of %zu Bucket-words were censored in %s\n", censor_count, bucket->wordcount, filename);
//     return true;
// }
