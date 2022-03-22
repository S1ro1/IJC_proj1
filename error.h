// error.h
// Řešení IJC-DU1, příklad b), 21.3.2022
// Autor: Matej Sirovatka, FIT
// Přeloženo: gcc 10.2.1 20210110
// Hlavičkový soubor implementace error modulu

#ifndef ERROR_H
#define ERROR_H

extern void warning_msg(const char *fmt, ...);

extern void error_exit(const char *fmt, ...);
#endif
