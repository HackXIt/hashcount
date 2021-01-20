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
table_t init_hashtable_from_file(char const *filename);
unsigned int insert_word(table_t table, const char *word);
void print_table(table_t table);
void select_bucket_to_print(table_t table);
void clean_table(table_t table);
void bucket_selection(table_t table);

#endif