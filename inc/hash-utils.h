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

/************************************************
 * @brief This type-definition allows list-utils to be internal.
 * 
 * Without it, I would need to include list-utils in hashcount.c
 * 
 ***********************************************/
typedef struct Bucket **table_t;

// bucket_t **init_hashtable();
// unsigned int insert_word(bucket_t **table, const char *word);
// void print_table(bucket_t **table);
// void select_bucket_to_print(bucket_t **table);
// void clean_table(bucket_t **table);
// void bucket_selection(bucket_t **table);

/************************************************
 * @brief Initializes a hash-table with NULL pointers.
 * 
 * @return table_t Returns a hash-table without data.
 ***********************************************/
table_t init_hashtable();
/************************************************
 * @brief Initializes and directly fills a hash-table with words from a text file.
 * 
 * This function initializes a hashtable with @link init_hashtable() @endlink and
 * immidiatly fills it with the words that are parsed from the provided filename.
 * The file is read line by line using getline.
 * 
 * @note The getline function automatically re-allocates the buffer-variable if the line is longer. 
 * It needs to be free'd manually.
 * 
 * @param filename The name of the file which will be parsed for words.
 * @return table_t Returns a hash-table with data from the file.
 ***********************************************/
table_t init_hashtable_from_file(const char *filename);
/************************************************
 * @brief Inserts a word into the hash-table.
 * 
 * This function alphabetically inserts a word into the provided hash-table.
 * If the calculated hash-index is NULL, a new double-linked list is generated and the word becomes the first entry.
 * If word-collisions occur, the new word is inserted alphabetically into the existing double-linked list.
 * 
 * @note word-collisions are inserted alphabetically from the start, to avoid usage of sorting-functions.
 * 
 * @param table the hashtable in which the word will be inserted.
 * @param word the word-string without delimiters to be inserted.
 * @param delimiters the delimiters of the word-string, to accurately censor words afterwards.
 * @return unsigned int the function returns a boolean value or 0/1 to determine the sucess/failure of the function-call.
 ***********************************************/
unsigned int insert_word(table_t table, const char *word, const char *delimiters);
/************************************************
 * @brief Outputs the complete hash-table to stdout.
 * 
 * Each bucket in the table is printed using the @link list-utils.h list-utils @endlink function @link print_bucket() @endlink.  
 * 
 * @param table the hashtable to be printed.
 ***********************************************/
void print_table(table_t table);
/************************************************
 * @brief Opens user-interaction to print specific word-buckets that the user wants to see.
 * 
 * @param table the hashtable to be used for the interaction.
 ***********************************************/
void select_bucket_to_print(table_t table);
/************************************************
 * @brief Clears all dynamically allocated memory of the hashtable.
 * 
 * @param table the hashtable to be free'd from memory.
 ***********************************************/
void clean_table(table_t table);
/************************************************
 * @brief Opens user-interaction to select specific word-buckets. A summary of the selection is printed at the end.
 * 
 * This function is an alternative to @link select_bucket_to_print() @endlink
 * It was adapted in @link censor_bucket_selection() @endlink to censor all selected word-buckets. 
 * 
 * @param table the hashtable to be used for the interaction.
 ***********************************************/
void simple_bucket_selection(table_t table);
/************************************************
 * @brief Opens user-interaction to select specific word-buckets for censoring.
 * 
 * This function is an adaption from @link simple_bucket_selection() @endlink to censor all selected word-buckets
 * from the provided input file. The censored result is written to the output-file.
 * 
 * @param table the hashtable to be used for the interaction.
 * @param input_file the name of the input-file.
 * @param output_file the name of the output-file.
 ***********************************************/
void censor_bucket_selection(table_t table, const char *input_file, const char *output_file);
/************************************************
 * @brief Censors the words from a single bucket in output file.
 * 
 * This function copies the contents of the input-file to the output-file character-by-character.
 * Then it censors the words from the bucket_number in the output-file.
 * 
 * If the bucket_number is out of range for the given table, an error message is printed and nothing will be done.
 * 
 * @param table the hashtable containing the buckets.
 * @param bucket_num the bucket_number to be used for censoring.
 * @param input_file the name of the input_file.
 * @param output_file the name of the output_file.
 ***********************************************/
void censor_file_with_bucket(table_t table, unsigned int bucket_num, const char *input_file, const char *output_file);
// void clear_file_with_bucket(table_t table, unsigned int bucket_num, const char *input_file, const char *output_file);
/************************************************
 * @brief Prints only the given bucket_number from the hash-table.
 * 
 * This function only prints the give bucket_number from the hash-table.
 * 
 * If the bucket_number is out of range for the given table, an error message is printed and nothing will be done.
 * 
 * @param table the hashtable containing the buckets.
 * @param bucket_num  the bucket_number to be printed.
 ***********************************************/
void print_selection(table_t table, unsigned int bucket_num);

#endif