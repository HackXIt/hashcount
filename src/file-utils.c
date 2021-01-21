/* FILE UTILS.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:51:22 AM
 * Last edited:
 *   1/21/2021, 10:31:03 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains all file-utility functions
**/

/*--- COMMON LIBRARIES ---*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

/*--- CUSTOM LIBRARIES ---*/
#include "list-utils.h"

/*--- MACROS ---*/
#define MAX_DUMP 100

/*
I need a function which reads a line from the FILE-Stream,
and inserts it into the hashtable.
*/

FILE *open_file(const char *filename, const char *mode)
{
    FILE *f_input = fopen(filename, mode);
    if (f_input == NULL)
    {
        fprintf(stderr, "Couldn't open file %s!\n", filename);
        return NULL;
    }
    return f_input;
}

void close_file(FILE *file)
{
    if (fclose(file) != 0)
    {
        fprintf(stderr, "Error when trying to close file.\n");
    }
}

unsigned int copy_file(const char *filename_in, const char *filename_out)
{
    FILE *file_in = open_file(filename_in, "r");
    FILE *file_out = open_file(filename_out, "w");
    if (file_in == NULL)
    {
        fprintf(stderr, "Error opening input-file: \"%s\"\n", filename_in);
        return false;
    }
    if (file_out == NULL)
    {
        fprintf(stderr, "Error opening output-file: \"%s\"\n", filename_out);
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

unsigned int censor_bucket_in_file(const char *filename, const bucket_t *bucket)
{
    FILE *to_censor = open_file(filename, "r");
    if (to_censor == NULL)
    {
        fprintf(stderr, "Error opening file to be censored: \"%s\"\n", filename);
        return false;
    }
    item_t *instance = bucket->start;
    /* NOTE Function-Pointer improvement
    Once I used copy-paste to re-use the below censor-algorithm from submission 11, I thought to myself:
    A function which reads the input-file and executes another function would be great for this.
    That would be a nice usage for function-pointers to learn... but oh hey 27 hours until deadline, I don't have time for this.
    So let's just keep that as a note for potential future iterations.
    */
    char dump[MAX_DUMP];
    char *censor_sub = NULL;
    unsigned int censor_count = 0;
    fpos_t prev_pos;
    fgetpos(to_censor, &prev_pos);
    /* WORD-CENSORING */
    while (fgets(dump, MAX_DUMP, to_censor) != NULL)
    {
        while (instance != NULL)
        {
            size_t len = strlen(instance->word);
            while ((censor_sub = strstr(dump, instance->word)) != NULL)
            {
                memset(censor_sub, '*', len);
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
    }
    close_file(to_censor);
    printf("A total of %u words were censored in %s\n", censor_count, filename);
    return true;
}
