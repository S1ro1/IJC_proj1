#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning_msg(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "CHYBA: ");
    vprintf(fmt, args);
    va_end(args);
}

void error_exit(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "CHYBA: ");
    vprintf(fmt, args);
    va_end(args);
    exit(1);
}