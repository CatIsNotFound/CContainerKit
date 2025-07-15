#include "CContainerKit/CDebug.h"

void printstr(const char* string, const char end_char) {
    printf("%s%c", string, end_char);
}

void printstrs(bool space, bool endLine, uint32_t count, ...) {
    va_list s_list;
    va_start(s_list, count);
    for (uint32_t i = 0; i < count; ++i) {
        if (!space)
            printf("%s", va_arg(s_list, const char*));
        else
            printf("%s ", va_arg(s_list, const char*));
    }
    if (endLine) { printLine(); }
    va_end(s_list);
}

void setMessageFormat(const char* format) {
    strcpy_s(c_format, 128, format);
}

void _strcat(char* dest, size_t start_pos, const char* src) {
    for (size_t i = 0; i < strlen(src); ++i) {
        dest[start_pos + i] = src[i];
    }
}

char* _translate(const char* type, const char* message) {
    time_t date = time(NULL);
    struct tm* now = localtime(&date);
    char date_time[64];
    char year[5], mouth[3], day[3],
         hour_24[3], hour_12[3], minute[3], second[3], am_pm[3];
    char* output = (char*)malloc(1024);
    memset(output, 0, 1024);
    size_t o_idx = 0;
    for (size_t i = 0; i < strlen(c_format); ) {
        if (c_format[i] == '%') {
            switch (c_format[++i]) {
                case 'T':
                    _strcat(output, o_idx, type);
                    o_idx += strlen(type);
                    break;
                case 't':
                    _strcat(output, o_idx, message);
                    o_idx += strlen(message);
                    break;
                case 'Y':
                    strftime(year, 5, "%Y", now);
                    _strcat(output, o_idx, year);
                    o_idx += strlen(year);
                    break;
                case 'm':
                    strftime(mouth, 3, "%m", now);
                    _strcat(output, o_idx, mouth);
                    o_idx += strlen(mouth);
                    break;
                case 'd':
                    strftime(day, 3, "%d", now);
                    _strcat(output, o_idx, day);
                    o_idx += strlen(day);
                    break;
                case 'H':
                    strftime(hour_24, 3, "%H", now);
                    _strcat(output, o_idx, hour_24);
                    o_idx += strlen(hour_24);
                    break;
                case 'I':
                    strftime(hour_12, 3, "%I", now);
                    _strcat(output, o_idx, hour_12);
                    o_idx += strlen(hour_12);
                    break;
                case 'M':
                    strftime(minute, 3, "%M", now);
                    _strcat(output, o_idx, minute);
                    o_idx += strlen(minute);
                    break;
                case 'S':
                    strftime(second, 3, "%S", now);
                    _strcat(output, o_idx, second);
                    o_idx += strlen(second);
                    break;
                case 'p':
                    strftime(am_pm, 3, "%p", now);
                    _strcat(output, o_idx, am_pm);
                    o_idx += strlen(am_pm);
                    break;

            }
            i += 1;
        } else if (c_format[i] == '\\') {
            i += 1;
            continue;
        } else {
            output[o_idx++] = c_format[i++]; 
        }
    }
    output[o_idx] = '\0';
    return output;
}

void throwError(const char* message) {
    char* msg = _translate(CLEVEL_ERROR, message);
    printf("%s\n", msg);
    free(msg);
}

void debug(const char* string) {
    char* msg = _translate(CLEVEL_DEBUG, string);
    printf("%s\n", msg);
    free(msg);
}

void info(const char* string) {
    char* msg = _translate(CLEVEL_INFO, string);
    printf("%s\n", msg);
    free(msg);
}

void warning(const char* string) {
    char* msg = _translate(CLEVEL_WARNING, string);
    printf("%s\n", msg);
    free(msg);
}

void critical(const char* string) {
    char* msg = _translate(CLEVEL_CRITICAL, string);
    printf("%s\n", msg);
    free(msg);
}

