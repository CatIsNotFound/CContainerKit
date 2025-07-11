
#ifndef CVECTORSUITE_CSTRING_H
#define CVECTORSUITE_CSTRING_H
#include "CVariant.h"
#include <string.h>

typedef struct String {
    char* c_str;      // 字符串
    size_t length;    // 长度
} CString;

size_t _CStrLength(const char *string);
char * _CStrCopy(const char* str, size_t* len);
char * _CStrSub(const char* str, size_t start, size_t end, size_t* len);
const char *_CStrUpper(const char *str);
const char *_CStrLower(const char *str);
CString string(const char* str);
void strInit(uint32_t length, char default_char);
void strNewString(CString *string, const char *c_str);
bool strCompare(CString *str1, CString *str2, bool capital_sense);
bool strCompareWithCStr(CString *str1, const char *str2, bool capital_sense);
void strInsertOne(CString* str, size_t index, char ch);
void strPushBack(CString* str, char ch);
void strPushFront(CString* str, char ch);
void strRemoveOne(CString* str, size_t index);
void strPopBack(CString* str);
void strPopFront(CString* str);
CString strSub(CString* str, size_t start, size_t end);
CString strSubN(CString* str, size_t start, uint32_t count);
size_t strSubFind(CString* str, const char* keyword, bool capital_sense);
size_t strSubRFind(CString* str, const char* keyword, bool capital_sense);


#endif //CVECTORSUITE_CSTRING_H
