
#include "CContainerKit/CString.h"
#include <ctype.h>

char* _cstrset(char *s, int c) {
    size_t len = strlen(s);
    memset(s, c, len);
    return s;
}

bool _cstrCaseIsEqual(const char* s1, const char* s2) {
    if (strlen(s1) != strlen(s2)) return false;

    while (*s1 != '\0') {
        if (tolower(*s1) != tolower(*s2)) return false;
        s1++;
        s2++;
    }
    return true;
}

void _strFillZero(CString* string) {
    _cstrset(string->data, 0);
}

void _allocateData(CString* string, size_t new_length) {
    string->data = (char *) calloc(new_length + 1, sizeof(char));
    _cstrset(string->data, 0);
    string->capacity = new_length + 1;
}

CString string(const char* str) {
    CString new_str;
    size_t new_length = strlen(str);
    _allocateData(&new_str, new_length * 2);
    new_str.length = new_length;
    strcpy(new_str.data, str);
    return new_str;
}

CString strInit(const char ch, size_t length) {
    CString new_str;
    _allocateData(&new_str, length * 2);
    for (size_t i = 0; i < length; ++i) {
        new_str.data[i] = ch;
    }
    new_str.data[length] = '\0';
    new_str.length = length;
    return new_str;
}

void _destroyData(CString* string) {
    if (string->data) {
        free(string->data);
    }
}

void _destroyString(CString* string) {
    _destroyData(string);
    string->data = NULL;
    string->length = 0;
}


CString _strSub(CString* str, uint32_t start_pos, uint32_t count) {
    char* datas = (char*)malloc(str->length);
    _cstrset(datas, 0);
    for (size_t i = 0; i < count; ++i) {
        datas[i] = str->data[start_pos + i];
    }
    CString new_str = string(datas);
    free(datas);
    return new_str;
}

CString strList(const char* split, uint32_t count, ...) {
    va_list s_list;
    va_start(s_list, count);
    CArray str_array = arrayInit(count);
    size_t length = 0;
    for (size_t i = 0; i < count; ++i) {
        const char* str = va_arg(s_list, const char*);
        length += strlen(str);
        arrayModify(str_array, i, varString(str));
    }
    va_end(s_list);
    CString new_str = strInit('\0', (length + str_array.length - 1));
    for (size_t i = 0; i < str_array.length; ++i) {
        strcat(new_str.data, varStringData(str_array.elements[i]));
        if (i < str_array.length - 1) {
            strcat(new_str.data, split);
            length += strlen(split);
        }
    }
    deleteArray(str_array);
    return new_str;
}

void _strCopyStr(CString *string, const char *buffer) {
    if (strlen(buffer) + 1 >= string->capacity) {
        _destroyData(string);
        _allocateData(string, strlen(buffer) * 2);
    }
    _strFillZero(string);
    strcpy(string->data, buffer);
    string->length = strlen(buffer);
}

void _strInsertStr(CString *string, uint32_t index, const char *buffer) {
    if (index >= string->length) index = string->length;
    uint32_t s_len = strlen(string->data),
             b_len = strlen(buffer),
             new_length = s_len + b_len;
    if (new_length + 1 >= string->capacity) {
        char* old_str = (char*) malloc(s_len + 1);
        strcpy(old_str, string->data);
        _destroyData(string);
        _allocateData(string, (new_length) * 2);
        strcpy(string->data, old_str);
        free(old_str);
    }
    string->length = new_length;
    string->data[string->length] = '\0';

    for (size_t i = 0; i < s_len - index; ++i) {
        string->data[new_length - i - 1] = string->data[s_len - i - 1];
    }
    string->data[new_length] = '\0';
    for (size_t i = 0; i < strlen(buffer); ++i) {
        string->data[index + i] = buffer[i];
    }
}

void _strRemoveStr(CString *string, uint32_t index, uint32_t count) {
    if (index >= string->length || !count) return;
    if (count > string->length - index) count = string->length - index;
    uint32_t ed_pos = (index + count >= string->length ? string->length : index + count);
    for (uint32_t i = index; i < ed_pos; ++i) {
        string->data[i] = '\0';
    }
    uint32_t replace_idx_pos = index;
    for (uint32_t i = ed_pos; i < string->length; ++i) {
        string->data[replace_idx_pos++] = string->data[i];
    }
    string->length -= ed_pos - index;
    string->data[string->length] = '\0';
}

bool _strIsEqual(CString* string, const char* buffer, bool case_sensitive) {
    if (case_sensitive) {
        return strcmp(string->data, buffer) == 0;
    } else {
        return _cstrCaseIsEqual(string->data, buffer);
    }
}

bool _strIsContain(CString* string, const char* buffer, bool case_sensitive) {
    size_t buf_len = strlen(buffer);
    char* get_sub_str = (char*) malloc(buf_len + 1);
    for (size_t i = 0; i <= string->length - buf_len; ++i) {
        for (size_t j = 0; j < buf_len; ++j) {
            get_sub_str[j] = string->data[i + j];
        }
        get_sub_str[buf_len] = '\0';
        if (case_sensitive) {
            if (!strcmp(get_sub_str, buffer)) {
                free(get_sub_str);
                return true;
            }
        } else {
            if (_cstrCaseIsEqual(get_sub_str, buffer)) {
                free(get_sub_str);
                return true;
            }
        }
    }
    free(get_sub_str);
    return false;
}

void _strUpper(CString* string) {
    for (uint32_t i = 0; i < string->length; ++i) {
        if (string->data[i] >= 'a' && string->data[i] <= 'z') {
            string->data[i] -= ' ';
        }
    }
}

void _strLower(CString* string) {
    for (uint32_t i = 0; i < string->length; ++i) {
        if (string->data[i] >= 'A' && string->data[i] <= 'Z') {
            string->data[i] += ' ';
        }
    }
}

CVector _splitToVector(CString* str, const char split) {
    CVector find_idx = vectorInit(0);
    for (size_t i = 0; i < str->length; ++i) {
        if (str->data[i] == split) {
            vecPushBack(find_idx, varULongLong(i));
        }
    }
    if (find_idx.length == 0) {
        CVector vector = vectorInit(0);
        vecPushBack(vector, varString(str->data));
        destroyVector(find_idx);
        return vector;
    }
    vecPushBack(find_idx, varULongLong(strlen(str->data) + 1));
    size_t idx = 0;
    CVector vector = vectorInit(find_idx.length);
    for (size_t i = 0; i < find_idx.length; ++i) {
        char* sub_str = calloc(str->length + 1, sizeof(char));
        uint64_t key_pos = varULongLongData(find_idx.elements[i]);
        uint64_t pos = 0;
        for (uint64_t j = idx; j < key_pos; ++j) {
            sub_str[pos++] = str->data[j];
        }
        sub_str[pos] = '\0';
        CVariant var_str = varString(sub_str);
        vecModify(vector, i, var_str);
        idx = key_pos + 1;
        free(sub_str);
    }
    destroyVector(find_idx);
    return vector;
}

CVector _strToVector(CString* str) {
    CVector vec = vectorInitType(TYPE_INT8, str->length);
    for (size_t i = 0; i < str->length; ++i) {
        vecModify(vec, i, varChar(str->data[i]));
    }
    return vec;
}

