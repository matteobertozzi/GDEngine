#include "imagereader.h"
#include "macros.h"
#include "alloc.h"

static GDBool __isDdsImage (FILE *fh) {
    unsigned char magic[4];

    fseek(fh, 0, SEEK_SET);
    if (fread(magic, sizeof(unsigned char), 4, fh) != 4)
        return(GD_FALSE);

    return(!memcmp(magic, "DDS ", 4));
}

static GDImage *__ddsImageRead (GDImage *image, FILE *fh) {
    return(NULL);
}

GDImagePlugin __image_dds = {
    .name = "DDS",
    .isFormat = __isDdsImage,
    .mipMapCount = NULL,
    .readMipMap = NULL,
    .readImage = __ddsImageRead,    
};
