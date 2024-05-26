#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

FILE* openFile(const char * fileName, const char * mode);
void printFileContent(FILE *f);

#endif