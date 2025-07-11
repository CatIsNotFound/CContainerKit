#include "CContainerKit/CString.h"

size_t _CStrLength(const char *string) {
    size_t len = 0;
    while (string[len++] != '\0');
    return len;
}

char * _CStrCopy(const char* str, size_t* len) {
    size_t s_len = _CStrLength(str);
    if (len) *len = s_len;
    char* c_str = (char*) calloc(s_len + 1, sizeof(char));
    if (!c_str) {
        if (len) *len = 0;
        return NULL;
    }
    memcpy_s(c_str, sizeof(char), str, s_len);
    c_str[s_len] = '\0';
    return c_str;
}

char * _CStrSub(const char* str, size_t start, size_t end, size_t* len) {
    uint64_t real_len = end - start + 1;
    char c_str[real_len];
    size_t i = start;
    while (str[i] != '\0' && i < end) {
        c_str[i - start] = str[i];
        i += 1;
    }
    c_str[real_len] = '\0';
    if (len) *len = real_len;
    return c_str;
}

const char *_CStrUpper(const char *str) {
    uint64_t real_len = _CStrLength(str);
    char new_str[real_len];
    size_t i = 0;
    do {
        if (str[i] >= 'a' && str[i] <= 'z') {
            new_str[i] = (char)(str[i] - 32);
        } else {
            new_str[i] = str[i];
        }
    } while (str[i++] != '\0');
    return new_str;
}

const char *_CStrLower(const char *str) {
    size_t real_length = _CStrLength(str);
    char new_str[real_length];
    size_t i = 0;
    do {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            new_str[i] = (char)(str[i] + 32);
        } else {
            new_str[i] = str[i];
        }
    } while (str[i] != '\0');
    return new_str;
}

CString string(const char* str) {
    CString new_str;
    new_str.c_str = _CStrCopy(str, &new_str.length);
    return new_str;
}

void strInit(uint32_t length, char default_char) {
    CString new_str;
    char c_str[length];
    for (size_t i = 0; i < length; ++i) {
        c_str[i] = default_char;
    }
    c_str[length] = '\0';
    new_str.length = length;
}

void strNewString(CString *string, const char *c_str) {
    if (string) _CStrCopy(c_str, &string->length);
}

bool strCompare(CString *str1, CString *str2, bool capital_sense) {
    if (!str1 || !str2) return false;
    if (str1->length != str2->length) return false;
    char *comp1, *comp2;
    if (!capital_sense) {
        comp1 = _CStrLower(str1->c_str);
        comp2 = _CStrLower(str2->c_str);
    }
    for (size_t i = 0; i < str1->length; ++i) {
        if (comp1[i] != comp2[i]) return false;
    }
    return true;
}

bool strCompareWithCStr(CString *str1, const char *str2, bool capital_sense) {
    static size_t len;
    if (!str1 || !str2) return false;
    char *comp1, *comp2;
    if (!capital_sense) {
        comp1 = _CStrLower(str1->c_str);
        comp2 = _CStrLower(str2);
    } else {
        comp1 = str1->c_str;
        comp2 = _CStrCopy(str2, &len);
    }
    for (size_t i = 0; i < str1->length; ++i) {
        if (comp1[i] != comp2[i]) return false;
    }
    return true;
}

void strInsertOne(CString* str, size_t index, char ch) {
    for (size_t i = 0; i <= str->length - index; ++i) {
        // str->c_str[str->length - i] = str->c_str[str->length - i - 1];
    }
//    str->c_str[index] = ch;
    str->length += 1;
}

void strPushBack(CString* str, char ch) {
    strInsertOne(str, str->length, ch);
}

void strPushFront(CString* str, char ch) {
    strInsertOne(str, 0, ch);
}

void strRemoveOne(CString* str, size_t index) {
    for (size_t i = index; i < str->length; ++i) {
//        str->c_str[i] = str->c_str[i + 1];
    }
//    str->c_str[str->length - 1] = '\0';
    str->length -= 1;
}

void strPopBack(CString* str) {
    strRemoveOne(str, str->length - 1);
}

void strPopFront(CString* str) {
    strRemoveOne(str, 0);
}

CString strSub(CString* str, size_t start, size_t end) {
    CString new_str;
    new_str.c_str = _CStrSub(str->c_str, start, end, &new_str.length);
    return new_str;
}

CString strSubN(CString* str, size_t start, uint32_t count) {
    CString new_str;
    new_str.c_str = _CStrSub(str->c_str, start, start + count - 1, &new_str.length);
    return new_str;
}

size_t strSubFind(CString* str, const char* keyword, bool capital_sense) {
    return SIZE_MAX;
}

size_t strSubRFind(CString* str, const char* keyword, bool capital_sense) {
    return SIZE_MAX;
}
