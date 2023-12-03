#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long uint32_t;
typedef unsigned char uint8_t;

/* PNG Header and Critical Chunk:

 PNG datastream begin with a PNG signature(PNG Header) and is followed by and IHDR chunk.
 PNG signature is used to identify.*/

typedef struct {
    /* PNG Header */
    uint8_t signature[8];
    
    /* Length and Type of chunk */
    uint32_t length;
    uint32_t type;

    /* IHDR chunk */
    uint32_t width;
    uint32_t height;
    uint8_t bit_depth;
    uint8_t color_type;
    uint8_t compression_method;
    uint8_t filter_method;
    uint8_t interface_method;
} PNGDataStream;

uint32_t swap_endianness_uint32(uint32_t value);
PNGDataStream *decode_graph_file(FILE *graphFileDesc);

#endif