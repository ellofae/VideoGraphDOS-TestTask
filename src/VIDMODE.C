#include "VIDMODE.H"
#include "DECODER.H"

png_bytep *row_pointers;

png_bytep* decode_png(char *filename, uint8_t bit_depth, uint8_t color_type, uint32_t i_width, uint32_t i_height) {
    FILE *fp = fopen(filename, "rb");
    unsigned int y;

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png) {
        return NULL;
    }

    png_infop info = png_create_info_struct(png);
    if(!info) {
        return NULL;
    }

    if (setjmp(png_jmpbuf(png))) {
        return NULL;
    }
    png_init_io(png, fp);
    png_read_info(png, info);

    png_uint_32 width = (png_uint_32) i_width;
    png_uint_32 height = (png_uint_32) i_height;
    
    if (bit_depth == 16)
        png_set_strip_16(png);
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);
    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);
    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
    
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    
    if (color_type == PNG_COLOR_TYPE_GRAY ||
            color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    
    png_set_gray_to_rgb(png);
    png_read_update_info(png, info);
    
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }
    
    png_read_image(png, row_pointers);
    fclose(fp);

    return row_pointers;
}

void rgb_rgba_processing(uint32_t i_width, uint32_t i_height) {
    uint8_t counter = 0;

    int x, y;
    png_uint_32 height = (png_uint_32) i_height;
    png_uint_32 width = (png_uint_32) i_width;

    for (y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for (x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);
            png_byte old[4 * sizeof(png_byte)];

            memcpy(old, px, sizeof(old));

            px[0] = 255 - old[0];
            px[1] = 255 - old[1];
            px[2] = 255 - old[2];
        }
    }
}