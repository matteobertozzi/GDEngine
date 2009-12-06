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
