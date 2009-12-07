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

#ifndef _GDENGINE_IMAGE_H_
#define _GDENGINE_IMAGE_H_

#include <GDEngine/Object.h>
#include <GDEngine/Types.h>

typedef enum {
    GD_IMAGE_FORMAT_UNKNOWN,
    GD_IMAGE_FORMAT_RGB,
    GD_IMAGE_FORMAT_RGBA,

    GD_IMAGE_FORMAT_DXT1,
    GD_IMAGE_FORMAT_DXT2,
    GD_IMAGE_FORMAT_DXT5,
    GD_IMAGE_FORMAT_PVRTC_2BPPV1,
    GD_IMAGE_FORMAT_PVRTC_4BPPV1,
} GDImageFormat;

typedef struct {
    GD_OBJECT

    GDImageFormat format;
    GDUInt height;
    GDUInt width;
    GDUInt size;
    GDByte *data;
    char *name;

    GDUInt id;
} GDImage;

#define  gdImage(p)      ((GDImage *)(p))

GDBool gdImageFormatIsCompressed (GDImageFormat format);

GDImage *gdImageInit     (GDImage *image);
GDImage *gdImageRetain   (GDImage *image);
void     gdImageRelease  (GDImage *image);

GDImage *gdImageCopy     (GDImage *dst, const GDImage *src);

#define gdImageSetId(image, texId)      (image)->id = texId
void gdImageSetName   (GDImage *image, const char *name);
void gdImageSetFormat (GDImage *image, GDImageFormat format);
void gdImageSetSize   (GDImage *image, GDUInt width, GDUInt height);
void gdImageSetHeight (GDImage *image, GDUInt height);
void gdImageSetWidth  (GDImage *image, GDUInt width);
void gdImageSetData   (GDImage *image, GDByte *data, GDUInt size);

#endif /* !_GDENGINE_IMAGE_H_ */

