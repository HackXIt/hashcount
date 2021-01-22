/************************************************
 * @file hash-utils.h
 * @author Nikolaus Rieder (hackxit@gmail.com)
 * @brief The header file for the hash utilities. Mandatory for usage.
 * @version 0.1
 * @date 2021-01-22
 * 
 * @copyright Copyright (c) 2021
 * 
 ***********************************************/

#ifndef HASH_H
#define HASH_H

// typedef struct Hashtable
// {
//     struct Bucket **arr;
// } table_t;

typedef struct Bucket **table_t;

// bucket_t **init_hashtable();
// unsigned int insert_word(bucket_t **table, const char *word);
// void print_table(bucket_t **table);
// void select_bucket_to_print(bucket_t **table);
// void clean_table(bucket_t **table);
// void bucket_selection(bucket_t **table);

table_t init_hashtable();
table_t init_hashtable_from_file(const char *filename);
unsigned int insert_word(table_t table, const char *word, const char *delimiters);
void print_table(table_t table);
void select_bucket_to_print(table_t table);
void clean_table(table_t table);
void simple_bucket_selection(table_t table);
void censor_bucket_selection(table_t table, const char *input_file, const char *output_file);

#endif