#ifndef VIDMODE_H
#define VIDMODE_H

#include <stdio.h>
#include <png.h>
#include <stdint.h>

#define BUFSIZE 1024

png_bytep* decode_png(char *filename, uint8_t bit_depth, uint8_t color_type, uint32_t width, uint32_t height);
void rgb_rgba_processing(uint32_t i_width, uint32_t i_height);

#endif