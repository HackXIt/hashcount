#ifndef LIST_UTILS_H
#define LIST_UTILS_H

typedef struct Bucket
{
    item_t *start;
    item_t *end;
} bucket_t;

bucket_t *create_bucket(const char *word);
void append_item(bucket_t *bucket, const char *word);
item_t *search_bucket(const bucket_t *bucket, const char *word);
void print_bucket(const bucket_t *bucket);
void clean_bucket(const bucket_t *bucket);

#endif