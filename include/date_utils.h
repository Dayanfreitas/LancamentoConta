#ifndef date_utils_h
#define date_utils_h

#include <time.h>

char* dateNow();
struct tm getCurrentDate();
char* formatDateString(struct tm date);


#endif