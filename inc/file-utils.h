#ifndef FILE_UTILS_H
#define FILE_UTILS_H

FILE *open_file(const char *filename, const char *mode);
void close_file(FILE *file);
unsigned int copy_file(const char *filename_in, const char *filename_out);
unsigned int censor_bucket_in_file(const char *filename, bucket_t *bucket);
#endif