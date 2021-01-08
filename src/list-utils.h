#ifndef LIST_UTILS_H
#define LIST_UTILS_H

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
typedef struct BucketItem
{
    char *word;
    size_t count;
    struct nodes node;
} item_t;
typedef struct Bucket
{
    item_t *start;
    item_t *end;
} bucket_t;

bucket_t *create_bucket(const char *word);
void append_item(bucket_t *bucket, const char *word);
item_t *search_bucket(const bucket_t *bucket, const char *word);
void print_bucket(const bucket_t *bucket);
void clean_bucket(bucket_t *bucket);
void sort_bucket(bucket_t *bucket);

#endif