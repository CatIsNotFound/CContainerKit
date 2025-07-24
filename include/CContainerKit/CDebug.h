
#pragma once
#ifndef CVECTORSUITE_CDEBUG_H
#define CVECTORSUITE_CDEBUG_H
#include "CVariant.h"
#include <errno.h>
#include <time.h>

#define CLEVEL_DEBUG        "Debug"
#define CLEVEL_INFO         "Info"
#define CLEVEL_WARNING      "Warning"
#define CLEVEL_ERROR        "Error"
#define CLEVEL_CRITICAL     "Critical"

static char c_format[128] = "[%T] %t";

void setMessageFormat(const char* format);

void throwError(const char* message);
void debug(const char* string);
void info(const char* string);
void warning(const char* string);
void critical(const char* string);

#define printLine()             printf("\n")


#endif //CVECTORSUITE_CDEBUG_H
