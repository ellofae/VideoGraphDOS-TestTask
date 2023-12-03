#ifndef VIDMODE_H
#define VIDMODE_H

#include <stdio.h>
#include <dos.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define AH_SET_MODE 0x0
#define AL_VGA_COLOR_MODE 0x13
#define AL_VGA_COLOR_MODE_16 0x0D
#define VIDEO_INTERRUPT 0x10
#define VGA_TEXT_MODE 0x03

typedef unsigned char byte;

void set_pixels();
void set_mode(byte mode);
void displayWithVideoMode();
void read_png_file(char *filename);
void process_png(void);

#endif