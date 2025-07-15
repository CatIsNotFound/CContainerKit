
#pragma once
#ifndef CCONTAINERKIT_CSTRING_H
#define CCONTAINERKIT_CSTRING_H

#include "CVector.h"

typedef struct String {
    char* data;
    uint32_t length;
    uint32_t capacity;
} CString;

CString string(const char* str);
CString strInit(const char ch, size_t length);
void _allocateData(CString* string, size_t new_length);
void _destroyData(CString* string);
void _destroyString(CString* string);
void _strFillZero(CString* string);
CString _strSub(CString* str, uint32_t start_pos, uint32_t count);
CString strList(const char* split, uint32_t count, ...);
void _strCopyStr(CString *string, const char *buffer);
void _strInsertStr(CString *string, uint32_t index, const char *buffer);
void _strRemoveStr(CString *string, uint32_t index, uint32_t count);
bool _strIsEqual(CString* string, const char* buffer, bool case_sensitive);
bool _strIsContain(CString* string, const char* buffer, bool case_sensitive);
void _strUpper(CString* string);
void _strLower(CString* string);
CVector _splitToVector(CString* str, const char split);
CVector _strToVector(CString* str);


#define destroyString(string)                           _destroyString(&string)
#define stringSub(string, start_pos, count)             _strSub(&string, start_pos, count)
#define stringCopy(string, buffer)                      _strCopyStr(&string, buffer)
#define stringInsert(string, index, buffer)             _strInsertStr(&string, index, buffer)
#define stringPushBack(string, buffer)                  stringInsert(string, string.length, buffer)
#define stringPushFront(string, buffer)                 stringInsert(string, 0, buffer)
#define stringAppend(string, buffer)                    stringPushBack(string, buffer)
#define stringRemove(string, index, count)              _strRemoveStr(&string, index, count)
#define stringPopBack(string, count)                    stringRemove(string, string.length - count, count)
#define stringPopFront(string, count)                   stringRemove(string, 0, count)
#define stringIsEqual(string, buffer, case_sensitive)   _strIsEqual(&string, buffer, case_sensitive)
#define stringIsContain(string, buffer, case_sensitive) _strIsContain(&string, buffer, case_sensitive)
#define stringUpper(string)                             _strUpper(&string)
#define stringLower(string)                             _strLower(&string)
#define stringSplit(string, char)                       _splitToVector(&string, char)
#define stringToVector(string)                          _strToVector(&string)

#define forEachChar(string, ch)             \
ch = string.data[0];                        \
for (size_t i = 0; i < string.length; ++i, ch = string.data[i])

#define forEachCharPtr(string, ch)             \
ch = string->data[0];                          \
for (size_t i = 0; i < string->length; ++i, ch = string->data[i])

#endif //CCONTAINERKIT_CSTRING_H
