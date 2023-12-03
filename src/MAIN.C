#include <stdio.h>
#include <stdlib.h>

#include "FILEOPS.H"
#include "DECODER.H"
#include "VIDMODE.H"

int main(int argc, char **argv) {
    int key;

	if (argc != 2) {
        fprintf(stderr, "Error: incorrect number of params passed\n");
        return EXIT_FAILURE;
    }

    FILE *fp = open_graph_file(*(argv + 1));
    if(fp == NULL) {
        fprintf(stderr, "Error: couldn't open the file\n");
        return EXIT_FAILURE;
    }
    PNGDataStream * dv = decode_graph_file(fp);
    if (dv == NULL) {
        fclose(fp);
        return EXIT_FAILURE;
    }

    getc(stdin);
    if(decode_png(*(argv+1), dv->bit_depth, dv->color_type, dv->width, dv->height) == NULL) {
        fprintf(stdout, "Error: decoding failed");
        fclose(fp);
    }

    rgb_rgba_processing(dv->width, dv->height);

    fclose(fp);

    return EXIT_SUCCESS;
}