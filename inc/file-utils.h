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

/************************************************
 * @brief Opens the given filename with fopen() in the provided mode.
 * 
 * This function is totally redundant, but makes my code more readable,
 * because I don't need to write the error-handling multiple times.
 * 
 * @param filename the filename to be opened.
 * @param mode the mode in which the filename will be opened
 * @return FILE* returns a FILE-stream pointer or NULL if fopen() failed.
 ***********************************************/
FILE *open_file(const char *filename, const char *mode);
/************************************************
 * @brief Closes the given filename with fclose().
 * 
 * This function is totally redundant, but makes my code more readable,
 * because I don't need to write the error-handling multiple times.
 * 
 * @param file the FILE-stream pointer to be closed.
 ***********************************************/
void close_file(FILE *file);
/************************************************
 * @brief Copies the contents from the input-file to the output-file, character by character.
 * 
 * This function opens the input- & output-file with the given filenames.
 * It then writes the contents from the input character-by-character to the output.
 * 
 * @param filename_in the filename of the input-file.
 * @param filename_out the filename of the output-file.
 * @return unsigned int a boolean return value to determine the success of the function call.
 ***********************************************/
unsigned int copy_file(const char *filename_in, const char *filename_out);
/************************************************
 * @brief Censors all bucket-words in the given input-file.
 * 
 * This function reads AND writes to the SAME file.
 * It compares every word from the given bucket (including delimiters) to the buffer.
 * If a matching word is found, it is overwritten with asterisks.
 * The delimiters will be untouched by this.
 * 
 * @param filename the filename of the input-file 
 * @param bucket the bucket which contains the words to be censored.
 * @return unsigned int a boolean return value to determine the success of the function call.
 ***********************************************/
unsigned int censor_bucket_in_file(const char *filename, bucket_t *bucket);
#endif