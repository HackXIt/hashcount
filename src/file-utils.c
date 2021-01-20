/* FILE UTILS.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   1/5/2021, 11:51:22 AM
 * Last edited:
 *   1/20/2021, 10:16:54 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains all file-utility functions
**/

/*--- COMMON LIBRARIES ---*/
#include <stdlib.h>
#include <stdio.h>

/*--- CUSTOM LIBRARIES ---*/

/*--- MACROS ---*/

/*
I need a function which reads a line from the FILE-Stream,
and inserts it into the hashtable.
*/

FILE *open_file(char const *filename, char const *mode)
{
    FILE *f_input = fopen(filename, mode);
    if (f_input == NULL)
    {
        fprintf(stderr, "Couldn't allocate memory for file-stream!\n");
        return NULL;
    }
    return f_input;
}

void close_file(FILE *file)
{
    fclose(file);
    // free(file);
}