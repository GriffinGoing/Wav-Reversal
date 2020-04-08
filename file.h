#ifndef FILE_H
#define FILE_H
#include <stdlib.h>

size_t read_file(char* filename, char **buffer);

size_t write_file(char* filename, char *buffer, size_t size);

#endif
