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
    
    char buffer[4096];
        snprintf(buffer, 4095,
            "/Users/oz/Desktop/GDEngine/TombRaider/DATA/%s",
            strrchr(filename, '/'));
    filename = buffer;

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

