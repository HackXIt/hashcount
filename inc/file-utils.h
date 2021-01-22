/************************************************
 * @file file-utils.h
 * @author Nikolaus Rieder (hackxit@gmail.com)
 * @brief Header-file for file-utilities. For internal usage.
 * @version 0.1
 * @date 2021-01-22
 * 
 * @copyright Copyright (c) 2021
 * 
 ***********************************************/

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

FILE *open_file(const char *filename, const char *mode);
void close_file(FILE *file);
unsigned int copy_file(const char *filename_in, const char *filename_out);
unsigned int censor_bucket_in_file(const char *filename, bucket_t *bucket);
#endif