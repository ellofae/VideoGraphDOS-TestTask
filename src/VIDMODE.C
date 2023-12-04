#include "VIDMODE.H"
#include "DECODER.H"

byte far *VGA_BASE_ADDRESS = (byte far *)0xA0000000L;

#define SETPIXEL(x, y, pixel_color) *(VGA_BASE_ADDRESS + (x) + (y) * SCREEN_WIDTH) = pixel_color;
#define GETPIXEL(x,y) *(VGA_BASE_ADDRESS + (x) + (y) * SCREEN_WIDTH);

void set_mode(byte mode) {
    union REGS regs;
    regs.h.ah = AH_SET_MODE;
    regs.h.al = mode;
    int86(VIDEO_INTERRUPT, &regs, &regs);
}

void set_pixels() {
    int x, y;
    for(y = 0; y < SCREEN_HEIGHT; ++y) {
        for (x = 0; x < SCREEN_WIDTH; ++x) {
            SETPIXEL(x, y, y);
        }
    }
}

void displayWithVideoMode() {
    set_mode(AL_VGA_COLOR_MODE);
    set_pixels();

    getchar();
    getchar();

    set_mode(AL_VGA_COLOR_MODE_16);
    set_pixels();
}
