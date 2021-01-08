#ifndef HASH_H
#define HASH_H

bucket_t **init_hashtable();
unsigned int insert_word(bucket_t **table, const char *word);
void print_table(bucket_t **table);
void clean_table(bucket_t **table);

#endif