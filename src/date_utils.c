#include <stdio.h>
#include <time.h>

#include "../include/date_utils.h"

char* dateNow() {
	struct tm currentDate = getCurrentDate();
	return formatDateString(currentDate);
}

struct tm getCurrentDate() {
	time_t mytime;
	mytime = time(NULL);
	return *localtime(&mytime);
}

char* formatDateString(struct tm date) {
	static char dateString[11];
	snprintf(dateString, sizeof(dateString), "%02d/%02d/%04d", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900);
	return dateString;
}