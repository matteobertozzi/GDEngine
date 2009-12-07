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
#include "endian.h"
#include "alloc.h"

typedef struct {
    uint32_t headerLength;
    uint32_t height;
    uint32_t width;
    uint32_t numMipmaps;
    uint32_t flags;
    uint32_t dataLength;
    uint32_t bpp;
    uint32_t bitmaskRed;
    uint32_t bitmaskGreen;
    uint32_t bitmaskBlue;
    uint32_t bitmaskAlpha;
    uint32_t pvrTag;
    uint32_t numSurfs;
} PVRHeader;

typedef enum {
    PVR_FLAGS_PVRTC_2 = 24,
    PVR_FLAGS_PVRTC_4,
} PVRFlagsType;

static GDBool __isPvrImage (FILE *fh) {
    PVRHeader header;
    uint32_t pvrTag;

    if (fread(&header, sizeof(PVRHeader), 1, fh) != 1)
        return(GD_FALSE);

    pvrTag = gdLittle16ToHost(header.pvrTag);
    return(((pvrTag >>  0) & 0xff) != 'P' &&
           ((pvrTag >>  8) & 0xff) != 'V' &&
           ((pvrTag >> 16) & 0xff) != 'R' &&
           ((pvrTag >> 24) & 0xff) != '!');
}

static GDImage *__pvrImageRead (GDImage *image, FILE *fh) {
    PVRHeader header;

    if (fread(&header, sizeof(PVRHeader), 1, fh) != 1)
        return(NULL);

    return(NULL);
}

GDImagePlugin __image_pvr = {
    .name = "PVR",
    .isFormat = __isPvrImage,
    .mipMapCount = NULL,
    .readMipMap = NULL,
    .readImage = __pvrImageRead,    
};
