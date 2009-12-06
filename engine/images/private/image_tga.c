#include "imagereader.h"
#include "macros.h"
#include "alloc.h"

static GDBool __tgaIsUnCompressed (const unsigned char *header) {
    unsigned char uTGAhead[12] = { 0, 0,  2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    return(!memcmp(header, uTGAhead, 12));
}

static GDBool __tgaIsCompressed (const unsigned char *header) {
    unsigned char cTGAhead[12] = { 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    return(!memcmp(header, cTGAhead, 12));
}

static GDImage *__tgaUncompressedLoad (GDImage *image, FILE *fh) {
    GDUInt i, width, height, size;
    unsigned char header[6];
    GDUInt bpp, bpp8;
    GDByte *blob;

    if (fread(header, 6, 1, fh) != 1)
        return(NULL);

    height = header[3] * 256 + header[2];
    width = header[1] * 256 + header[0];
    bpp = header[4];

    if (width < 1 || height < 1 || ((bpp != 24) && (bpp != 32)))
        return(NULL);

    bpp8 = (bpp / 8);
    size = bpp8 * width * height;
    if ((blob = gdAllocArray(GDByte, size)) == NULL)
        return(NULL);

    if (fread(blob, 1, size, fh) != size) {
        gdFree(blob);
        return(NULL);
    }

    for (i = 0; i < size; i += bpp8)
        blob[i] ^= blob[i + 2] ^= blob[i] ^= blob[i + 2];

    if ((image = gdImageInit(image)) != NULL) {
        gdImageSetFormat(image, GD_IMAGE_FORMAT_RGB);
        gdImageSetSize(image, width, height);
        gdImageSetData(image, blob, size);
    }

    return(image);
}

static GDImage *__tgaCompressedLoad (GDImage *image, FILE *fh) {
    unsigned int i, pixel, pixelCount;
    GDUInt width, height, size;
    unsigned char chunkHeader;
    unsigned int currentByte;
    unsigned char header[6];
    GDUInt bpp, bpp8;
    char *colorBuffer;
    GDByte *blob;

    if (fread(header, 6, 1, fh) != 1)
        return(NULL);

    height = header[3] * 256 + header[2];
    width = header[1] * 256 + header[0];
    bpp = header[4];

    if (width < 1 || height < 1 || ((bpp != 24) && (bpp != 32)))
        return(NULL);

    bpp8 = (bpp / 8);
    pixelCount = width * height;
    size = bpp8 * pixelCount;
    if ((blob = gdAllocArray(GDByte, size)) == NULL)
        return(NULL);

    if ((colorBuffer = (char *) malloc(bpp8)) == NULL) {
        free(blob);
        return(NULL);
    }

    currentByte = pixel = 0;
    do {
        chunkHeader = 0;
        if (fread(&chunkHeader, sizeof(unsigned char), 1, fh) != 1) {
            free(blob);
            return(NULL);
        }

        if (chunkHeader < 128) {
            chunkHeader++;

            for (i = 0; i < chunkHeader; ++i) {
                if (fread(colorBuffer, 1, bpp8, fh) != bpp8) {
                    free(blob);
                    free(colorBuffer);
                    return(NULL);
                }

                blob[currentByte]   = colorBuffer[2];
                blob[currentByte+1] = colorBuffer[1];
                blob[currentByte+2] = colorBuffer[0];

                if (bpp8 == 4)
                    blob[currentByte+3] = colorBuffer[3];

                currentByte += bpp8;
                pixel++;
            }
        } else {
            chunkHeader += 127;

            if (fread(colorBuffer, 1, bpp8, fh) != bpp8) {
                free(blob);
                free(colorBuffer);
                return(NULL);
            }

            for (i = 0; i < chunkHeader; ++i) {
                blob[currentByte]   = colorBuffer[2];
                blob[currentByte+1] = colorBuffer[1];
                blob[currentByte+2] = colorBuffer[0];

                if (bpp8 == 4)
                    blob[currentByte+3] = colorBuffer[3];

                currentByte += bpp8;
                pixel++;
            }
        }
    } while (pixel < pixelCount);

    if ((image = gdImageInit(image)) != NULL) {
        gdImageSetFormat(image, GD_IMAGE_FORMAT_RGB);
        gdImageSetSize(image, width, height);
        gdImageSetData(image, blob, size);
    }

    return(image);
}

static GDBool __isTgaImage (FILE *fh) {
    unsigned char head[12];

    fseek(fh, 0, SEEK_SET);

    if (fread(head, sizeof(unsigned char), 12, fh) != 12)
        return(GD_FALSE);

    return(__tgaIsUnCompressed(head) || __tgaIsCompressed(head));
}

static GDImage *__tgaImageRead (GDImage *image, FILE *fh) {
    unsigned char head[12];

    fseek(fh, 0, SEEK_SET);

    /* Read TGA Header */
    if (fread(head, sizeof(unsigned char), 12, fh) != 12)
        return(NULL);

    if (__tgaIsUnCompressed(head)) {
        printf("Uncompressed\n");
        return(__tgaUncompressedLoad(image, fh));
    }

    if (__tgaIsCompressed(head)) {
        printf("Compressed\n");
        return(__tgaCompressedLoad(image, fh));
    }

    return(NULL);
}

GDImagePlugin __image_tga = {
    .name = "TGA",
    .isFormat = __isTgaImage,
    .mipMapCount = NULL,
    .readMipMap = NULL,
    .readImage = __tgaImageRead,    
};

