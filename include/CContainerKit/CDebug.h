
#pragma once
#ifndef CVECTORSUITE_CDEBUG_H
#define CVECTORSUITE_CDEBUG_H
#include "CVariant.h"
#include <errno.h>
#include <time.h>
#define TYPE    "$T"
#define TEXT    "$t"
#define YEAR    "$Y"
#define MONTH   "$m"
#define DAY     "$d"
#define HOUR    "$H"
#define MINUTE  "$M"
#define SECOND  "$S"

#define CLEVEL_DEBUG        "Debug"
#define CLEVEL_INFO         "Info"
#define CLEVEL_WARNING      "Warning"
#define CLEVEL_ERROR        "Error"
#define CLEVEL_CRITICAL     "Critical"

static char c_format[128] = "[%T] %t";

void printstr(const char* string, const char end_char);
void printstrs(bool space, bool endLine, uint32_t count, ...);

void setMessageFormat(const char* format);
void _strcat(char* dest, size_t start_pos, const char* src);
char* _translate(const char* type, const char* message);

void throwError(const char* message);
void debug(const char* string);
void info(const char* string);
void warning(const char* string);
void critical(const char* string);

#define printLine()             printf("\n")


#endif //CVECTORSUITE_CDEBUG_H
