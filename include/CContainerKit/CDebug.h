
#ifndef CVECTORSUITE_CDEBUG_H
#define CVECTORSUITE_CDEBUG_H
#include "CVariant.h"

typedef enum DebugLevel {
    DEBUG_INFO,
    DEBUG_WARNING,
    DEBUG_CRITICAL
} DebugLevel;

static void print(const char* str) {
    printf("%s\n", str);
}

#define printLine()             printf("\n")





#endif //CVECTORSUITE_CDEBUG_H
