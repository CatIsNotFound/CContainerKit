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

void setDebugFormat(const char* format) {
    strncpy(debug_format, format, (strlen(format) >= 64 ? 64 : strlen(format)));
}

void _translate(const char* message) {
    time_t date;
    struct tm* now = localtime(&date);

}

void throwError(const char* message) {

}
