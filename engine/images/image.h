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

