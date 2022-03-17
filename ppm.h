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