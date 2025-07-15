
#pragma once
#ifndef CVECTORSUITE_CDEBUG_H
#define CVECTORSUITE_CDEBUG_H
#include "CVariant.h"
#include <errno.h>
#include <time.h>
#define TYPE    "$t"
#define MESSAGE "$T"
#define YEAR    "$Y"
#define MONTH   "$m"
#define DAY     "$d"
#define HOUR    "$H"
#define MINUTE  "$M"
#define SECOND  "$S"

static char debug_format[64] = "[$t] $T";

void printstr(const char* string, const char end_char);
void printstrs(bool space, bool endLine, uint32_t count, ...);

void setDebugFormat(const char* format);
void _translate(const char* message);
void throwError(const char* message);
void debug(const char* string);
void warning(const char* string);
void critical(const char* string);

#define printLine()             printf("\n")





#endif //CVECTORSUITE_CDEBUG_H
