#ifndef DATETIME_H_DEFINED
#define DATETIME_H_DEFINED

#include <stdlib.h>
#include <string.h>

// ADT data e ora
typedef struct DateTime_s *DateTime_t;
struct DateTime_s{
    int year, month, day, hour, minute;
};

int cmpDate(DateTime_t d1, DateTime_t d2);

#endif // DATETIME_H_DEFINED