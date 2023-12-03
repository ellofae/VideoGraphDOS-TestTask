#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "FILEOPS.H"
#include "DECODER.H"
#include "VIDMODE.H"

void wait_func() {
    while(1) {
        if (kbhit()) {
            break;
        }
    }
}

int main(int argc, char **argv) {
    int key;

    clrscr();
	if (argc != 2) {
        fprintf(stderr, "Error: incorrect number of params passed\n");
        return EXIT_FAILURE;
    } else {
        FILE *fp = open_graph_file(*(argv + 1));
        if(fp == NULL) {
            fprintf(stderr, "Error: couldn't open the file\n");
            return EXIT_FAILURE;
        } else {
            PNGDataStream * dv = decode_graph_file(fp);
            if (dv == NULL) {
                fclose(fp);
                return EXIT_FAILURE;
            } else {     
                wait_func();
                displayWithVideoMode();
            }
            fclose(fp);
        }
    }

    wait_func();
    set_mode(VGA_TEXT_MODE);

    return EXIT_SUCCESS;
}