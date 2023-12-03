#include "FILEOPS.H"

FILE *open_graph_file(char *graphFileName) {
	FILE *fp = fopen(graphFileName, "rb");
	if (!fp) {
		return NULL;
	}

	return fp;
}