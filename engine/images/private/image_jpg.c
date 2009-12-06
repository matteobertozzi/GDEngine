#include <GDEngine/Config.h>

#if defined(GD_ENGINE_JPG_SUPPORT)

#include "imagereader.h"
#include "macros.h"
#include "alloc.h"

static GDBool __isJpgImage (FILE *fh) {
    return(GD_FALSE);
}

static GDImage *__jpgImageRead (GDImage *image, FILE *fh) {
    return(NULL);
}

GDImagePlugin __image_jpg = {
    .name = "JPG",
    .isFormat = __isJpgImage,
    .mipMapCount = NULL,
    .readMipMap = NULL,
    .readImage = __jpgImageRead,    
};

#endif

