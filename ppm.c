#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "error.h"
#include "ppm.h"

void ppm_free(struct ppm *p) {
    free(p);
}

struct ppm * ppm_read(const char *filename) {
    FILE *f = fopen(filename, "rb");

    if (f == NULL) {
        warning_msg("Couldn't open file %s", filename);
    }

    unsigned x_size;
    unsigned y_size;
    unsigned color_range;

    fscanf(f, "P6 %u %u %u ", &x_size, &y_size, &color_range);

    if (color_range != 255) {
        warning_msg("Unsupported color range %u", color_range);
        fclose(f);
        return NULL;
    }

    size_t calculated_img_size = x_size * y_size * 3;

    struct ppm* img = malloc(sizeof(struct ppm) + calculated_img_size);

    if (img == NULL) {
        warning_msg("Error allocating memory\n");
        fclose(f);
        return NULL;
    }

    img->xsize = x_size;
    img->ysize = y_size;

    size_t img_size = fread(img->data, sizeof(char), calculated_img_size, f);

    if (img_size != calculated_img_size) {
        warning_msg("Calculated size differs from real length\n");
        free(img);
        fclose(f);
        return NULL;
    }

    char c = fgetc(f);
    if (c != EOF) {
        putchar(c);

        warning_msg("No EOF found\n");
        fclose(f);
        free(img);
        return NULL;
    }

    fclose(f);
    return img;
}