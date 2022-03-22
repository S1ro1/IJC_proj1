// error.c
// Řešení IJC-DU1, příklad b), 21.3.2022
// Autor: Matej Sirovatka, FIT
// Přeloženo: gcc 10.2.1 20210110
// Zdrojový soubor implementace error modulu 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning_msg(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, args);

    va_end(args);
}

void error_exit(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, args);

    va_end(args);
    exit(1);
}
