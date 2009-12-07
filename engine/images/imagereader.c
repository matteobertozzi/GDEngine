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

#include <GDEngine/Config.h>

#include "imagereader.h"
#include "imagepool.h"
#include "macros.h"
#include "debug.h"
#include "list.h"

/* Load Default Image Plugins */
extern GDImagePlugin __image_bmp;
extern GDImagePlugin __image_dds;
extern GDImagePlugin __image_pvr;
extern GDImagePlugin __image_tga;

#if defined(GD_ENGINE_PNG_SUPPORT)
    extern GDImagePlugin __image_png;
#endif

#if defined(GD_ENGINE_JPG_SUPPORT)
    extern GDImagePlugin __image_jpg;
#endif

/* Internal Plugin Format List */
static GDList *__imageFormats = NULL;

static GDList *_gdImageFormats (void) {
    if (__imageFormats == NULL) {
        __imageFormats = gdListAlloc();

#if defined(GD_ENGINE_PNG_SUPPORT)
        gdListAppend(__imageFormats, &__image_png);
#endif
        gdListAppend(__imageFormats, &__image_dds);
        gdListAppend(__imageFormats, &__image_pvr);
#if defined(GD_ENGINE_JPG_SUPPORT)
        gdListAppend(__imageFormats, &__image_jpg);
#endif
        gdListAppend(__imageFormats, &__image_tga);
        gdListAppend(__imageFormats, &__image_bmp);
    }

    return(__imageFormats);
}

GDBool gdImageReaderAddPlugin (GDImagePlugin *plugin) {
    gdReturnValueIfNull(plugin, GD_FALSE);
    return(gdListAppend(_gdImageFormats(), plugin));
}

GDImage *gdImageReadFromFile (GDImage *image, const char *filename) {
    GDImagePlugin *plugin;
    GDImage *poolImg;
    GDList *formats;
    GDUInt i, n;
    FILE *fh;
    
    /* First, try to lookup Image in Pool */
    if ((poolImg = gdImagePoolFind(filename)) != NULL)
        return(image ? gdImageCopy(image, poolImg) : gdImageRetain(poolImg));

    formats = _gdImageFormats();
    GD_ASSERT(format != NULL, "Image Reader Unable to Initialize");

    if ((fh = fopen(filename, "rb")) == NULL) {
        //gdWarningSysFail("fopen(%s)", filename);
        return(NULL);
    }

    for (i = 0, n = gdListSize(formats); i < n; ++i) {
        plugin = gdImagePlugin(gdListAt(formats, i));

        if (plugin->readImage == NULL)
            continue;

        if (plugin->isFormat != NULL && !plugin->isFormat(fh))
            continue;

        /* If Image Loaded, add to Image Pool, and return. */
        if ((image = plugin->readImage(image, fh)) != NULL) {
            fprintf(stderr, "Loaded Image: %s\n", filename);
            gdImageSetName(image, filename);
            gdImagePoolAdd(image);
            break;
        }
    }

    fclose(fh);

    return(image);
}

GDImage *gdImageReadFromMipMap (GDImage *image,
                              GDMipMap *mipMap,
                              GDUInt level)
{
    return(NULL);
}

GDMipMap *gdMipMapReadFromFile (GDMipMap *mipMap, const char *filename) {
    GDImagePlugin *plugin;
    GDList *formats;
    GDUInt i, n;
    FILE *fh;

    formats = _gdImageFormats();
    GD_ASSERT(format != NULL, "Image Reader Unable to Initialize");

    if ((fh = fopen(filename, "rb")) == NULL) {
        gdWarningSysFail("fopen(%s)", filename);
        return(NULL);
    }

    for (i = 0, n = gdListSize(formats); i < n; ++i) {
        plugin = gdImagePlugin(gdListAt(formats, i));

        if (plugin->readImage == NULL)
            continue;

        if (plugin->isFormat != NULL && !plugin->isFormat(fh))
            continue;

        if ((mipMap = plugin->readMipMap(mipMap, fh)) != NULL)
            break;
    }

    fclose(fh);

    return(mipMap);
}

