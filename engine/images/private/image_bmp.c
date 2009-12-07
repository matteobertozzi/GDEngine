/*
 * Copyright (c) 2009, Matteo Bertozzi <theo.bertozzi@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Matteo Bertozzi nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Matteo Bertozzi ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Matteo Bertozzi BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

