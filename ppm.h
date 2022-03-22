// ppm.h
// Řešení IJC-DU1, příklad b), 21.3.2022
// Autor: Matej Sirovatka, FIT
// Přeloženo: gcc 10.2.1 20210110
// Hlavičkový soubor rozhraní pro načítaní .ppm souboru

#ifndef PPM_1_H
#define PPM_1_H

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

struct ppm * ppm_read(const char *filename);

void ppm_free(struct ppm *p);

#endif