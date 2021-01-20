#ifndef FILE_UTILS_H
#define FILE_UTILS_H

FILE *open_file(char const *filename, char const *mode);
void close_file(FILE *file);

#endif