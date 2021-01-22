/************************************************
 * @file list-utils.h
 * @author Nikolaus Rieder (hackxit@gmail.com)
 * @brief Header-file for list-utilities. For internal usage.
 * @version 0.1
 * @date 2021-01-22
 * 
 * @copyright Copyright (c) 2021
 * 
 ***********************************************/

#ifndef LIST_UTILS_H
#define LIST_UTILS_H

/************************************************
 * @brief This structure contains the next & previous nodes of the list.
 * 
 * I've implemented a seperate structure for the nodes to make the code more readable.
 * I find it a bit less confusing to read "node.next" vs "->next".
 * Otherwise, a recursive access to the double-linked list would read as: 
 * @code bucket->start->next->prev
 * 
 ***********************************************/
struct nodes
{
    /*
    This struct is only for readability
    I find it a bit less confusing to read "node.next" vs "->next".
    It also breaks the repeating syntax-pattern, which makes it more recognizable.
    Otherwise it would read bucket->start->next->prev ... or something like that.
    */
    struct BucketItem *next;
    struct BucketItem *prev;
};
/************************************************
 * @brief This structure contains the data of an individual item in the double-linked list.
 * 
 * The structure represents an individual item in the double-linked list and contains pointers to its links.
 * In this data-structure, multiple versions of the original word are stored.
 * word is the original word as it was written in the text.
 * lower_word is the lowercase version of the word, for easier ASCII-comparison.
 * word_with_delimiters is the original word including it's delimiters (before & after the word).
 * 
 ***********************************************/
typedef struct BucketItem
{
    char *word;
    char *lower_word;
    char *word_with_delimiters;
    size_t count;
    struct nodes node;
} item_t;
/************************************************
 * @brief This structure contains the start and end pointer of the double-linked list.
 * 
 * In this data-structure, the start and end pointer of the double-linked list are stored.
 * It represents the bucket to contain the items that need to be linked.
 * I've included a counter to easily output the number of items in the bucket.
 * 
 ***********************************************/
typedef struct Bucket
{
    item_t *start;
    size_t wordcount;
    item_t *end;
} bucket_t;

/************************************************
 * @brief Dynamically creates a double-linked list, with a starting item.
 * 
 * This function dynamically creates a double-linked list, a so called bucket.
 * It handles the memory allocation and will return a NULL pointer if no memory could be allocated.
 * 
 * @param word the string of the word to be stored in the newly generated item.
 * @param delimiters the delimiters before and after the word. Should always be a char-Array with size 2.
 * @return bucket_t* returns a pointer to the new bucket or NULL if the creation failed.
 ***********************************************/
bucket_t *create_bucket(const char *word, const char *delimiters);
/************************************************
 * @brief Appends a new item to the end of the double-linked list.
 * 
 * The function dynamically creates a new item from the provided word and delimiters.
 * The item is then appended to the bottom of the bucket (i.e. end of the list)
 * This function servers as an alternative to @see add_item_sorted()
 * It's much more simple and less error-prone but will inevitably make the list unsorted.
 * 
 * @param bucket the bucket, in which the item should be appended.
 * @param word the word used to dynamically create the new item.
 * @param delimiters the delimiters before and after the word. Should always be a char-Array with size 2.
 ***********************************************/
void append_item(bucket_t *bucket, const char *word, const char *delimiters);
/************************************************
 * @brief Adds a new item to the list, but retains alphabetical order of the list.
 * 
 * The function dynamically creates a new item from the provided word and delimiters.
 * The item is then compared to the list and inserted at it's correct alphabetical spot.
 * This function uses the lowercase version of the word for comparison, 
 * since uppercase ASCII-Letters are generally smaller than lowercase.
 * 
 * @param bucket the bucket, in which the item should be inserted.
 * @param word the word used to dynamically create the new item.
 * @param delimiters the delimiters before and after the word. Should always be a char-Array with size 2.
 ***********************************************/
void add_item_sorted(bucket_t *bucket, const char *word, const char *delimiters);
/************************************************
 * @brief Searches for an item in the double-linked list.
 * 
 * This function will search through the bucket and return a pointer to the first item found,
 * which matches the provided word.
 * If no word is found, a NULL pointer is returned.
 * 
 * @param bucket the bucket to be searched in.
 * @param word the word to be searched for, excluding delimiters.
 * @return item_t* returns a pointer to the found item or NULL if none was found.
 ***********************************************/
item_t *search_bucket(const bucket_t *bucket, const char *word);
/************************************************
 * @brief Prints the contents of the bucket to stdout.
 * 
 * This function outputs all words in the bucket in their listed order.
 * The function distinguishes between:
 * @li An empty list - Output: "-EMPTY-"
 * @li A list with a single item and it's occurence count if greater than 1.
 * @li A list with multiple items and their occurence count if greater than 1.
 * The items are seperated by a comma and a space.
 * 
 * @param bucket the bucket to be printed.
 ***********************************************/
void print_bucket(const bucket_t *bucket);
/************************************************
 * @brief Clears all dynamically allocated memory of the given bucket.
 * 
 * This function free's all dynamically allocated memory of the provided bucket.
 * 
 * @param bucket the bucket to be free'd from memory.
 ***********************************************/
void clean_bucket(bucket_t *bucket);

#endif