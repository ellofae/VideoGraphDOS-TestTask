#include "DECODER.H"

uint32_t swap_endians_uint32(uint32_t value) {
	return ((value >> 24) & 0x000000FF) | ((value >> 8) & 0x0000FF00) |
           ((value << 8) & 0x00FF0000) | ((value << 24) & 0xFF000000);
}

PNGDataStream *decode_graph_file(FILE *graphFileDesc) {
    PNGDataStream *chunk = (PNGDataStream *) malloc(sizeof(PNGDataStream));
    if(!chunk) {
        fprintf(stderr, "Error: unable to allocate memory for Data Stream struct\n");
        return NULL;
    } else {
		size_t read_size = fread(chunk, sizeof(uint8_t), sizeof(PNGDataStream), graphFileDesc);
		if(read_size != sizeof(PNGDataStream)) {
			fprintf(stderr, "Error: the data stream was not read fully\n");
			free(chunk);
			return NULL;
		}
	
		if (memcmp(chunk->signature, "\x89PNG\r\n\x1a\n", 8) != 0) {
			fprintf(stderr, "Error: invalid signature header\n");
			free(chunk);
			return NULL;
		}

		chunk->length = swap_endians_uint32(chunk->length);
		chunk->type = swap_endians_uint32(chunk->type);
		chunk->width = swap_endians_uint32(chunk->width);
		chunk->height = swap_endians_uint32(chunk->height);	
	}

    fprintf(stdout, "img width: %u\n", chunk->width);
    fprintf(stdout, "img height: %u\n", chunk->height);
    fprintf(stdout, "bit depth: %u\n", chunk->bit_depth);
    fprintf(stdout, "color type: %u\n", chunk->color_type);

    return chunk; 
}