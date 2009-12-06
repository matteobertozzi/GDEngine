#include "imagereader.h"
#include "macros.h"
#include "alloc.h"

static GDBool __isBmpImage (FILE *fh) {
    unsigned char magic[2];

    fseek(fh, 0, SEEK_SET);
    if (fread(magic, sizeof(unsigned char), 2, fh) != 2)
        return(GD_FALSE);

    return(!memcmp(magic, "BM", 2));
}

static GDImage *__bmpImageRead (GDImage *image, FILE *fh) {
    GDUInt32 width, height;
    GDUInt16 planes, bpp;
    GDUInt32 i, blobSize;
    GDByte color;
    GDByte *blob;

    /* Seek through the BMP header */
    fseek(fh, 18, SEEK_SET);

    /* Read Width/Height */
    if (fread(&width, sizeof(GDUInt32), 1, fh) != 1)
        return(NULL);

    if (fread(&height, sizeof(GDUInt32), 1, fh) != 1)
        return(NULL);

    /* Read the Planes, MUST BE 1 */
    if (fread(&planes, sizeof(GDUInt16), 1, fh) != 1)
        return(NULL);

    gdReturnValueIfFalse(planes == 1, NULL);

    /* Read the BPP, MUST BE 24 */
    if (fread(&bpp, sizeof(GDUInt16), 1, fh) != 1)
        return(NULL);

    gdReturnValueIfFalse(bpp == 24, NULL);

    /* Skip the Rest of the Header */
    fseek(fh, 24, SEEK_CUR);

    /* Calculate Blob Size */
    blobSize = (width * height * 3);

    /* Alloc Image Blob */
    blob = gdAllocArray(GDByte, blobSize);
    gdReturnValueIfNull(blob, NULL);

    /* Read Image Blob */
    if (fread(blob, blobSize, 1, fh) != 1) {
        gdFree(blob);
        return(NULL);
    }

    /* Reverse all the Colors (BGR -> RGB) */
    for (i = 0; i < blobSize; i += 3) {
        color = blob[i];
        blob[i] = blob[i + 2];
        blob[i + 2] = color;
    }

    /* Setup Image */
    if ((image = gdImageInit(image)) != NULL) {
        gdImageSetFormat(image, GD_IMAGE_FORMAT_RGB);
        gdImageSetSize(image, width, height);
        gdImageSetData(image, blob, blobSize);
    }

    return(image);
}

GDImagePlugin __image_bmp = {
    .name = "BMP",
    .isFormat = __isBmpImage,
    .mipMapCount = NULL,
    .readMipMap = NULL,
    .readImage = __bmpImageRead,    
};

