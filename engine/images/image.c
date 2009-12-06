#include "imagepool.h"
#include "object.h"
#include "alloc.h"
#include "image.h"

GDBool gdImageFormatIsCompressed (GDImageFormat format) {
    switch (format) {
        case GD_IMAGE_FORMAT_RGB:
        case GD_IMAGE_FORMAT_RGBA:
            return(GD_FALSE);
        case GD_IMAGE_FORMAT_DXT1:
        case GD_IMAGE_FORMAT_DXT2:
        case GD_IMAGE_FORMAT_DXT5:
        case GD_IMAGE_FORMAT_PVRTC_2BPPV1:
        case GD_IMAGE_FORMAT_PVRTC_4BPPV1:
            return(GD_TRUE);
        default:
            break;
    }
    return(GD_FALSE);
}

GDImage *gdImageInit (GDImage *image) {
    image = _gdObjectInit(GDImage, image);

    image->format = GD_IMAGE_FORMAT_UNKNOWN;
    image->height = 0;
    image->width = 0;
    image->size = 0;
    image->data = NULL;
    image->name = NULL;

    image->id = 0;
    return(image);
}

GDImage *gdImageRetain (GDImage *image) {
    _gdObjectRetain(gdObject(image));
    return(image);
}

void gdImageRelease (GDImage *image) {
    if (!_gdObjectRelease(gdObject(image)))
        return;

    gdImagePoolRemove(image);

    if (image->data != NULL)
        gdZFree(&(image->name));

    if (image->data != NULL)
        gdZFree(&(image->data));

    if (_gdObjectInternalAlloc(image))
        gdFree(image);
}

GDImage *gdImageCopy (GDImage *dst, const GDImage *src) {
    dst->format = src->format;
    dst->height = src->height;
    dst->width = src->width;
    dst->size = src->size;
    dst->name = strdup(src->name);

    dst->data = gdAllocArray(GDByte, dst->size);
    memcpy(dst->data, src->data, dst->size);

    return(dst);
}

void gdImageSetName (GDImage *image, const char *name) {    
    image->name = strdup(name);
}

void gdImageSetFormat (GDImage *image, GDImageFormat format) {
    image->format = format;
}

void gdImageSetSize (GDImage *image, GDUInt width, GDUInt height) {
    image->height = height;
    image->width = width;
}

void gdImageSetHeight (GDImage *image, GDUInt height) {
    image->height = height;
}

void gdImageSetWidth (GDImage *image, GDUInt width) {
    image->width = width;
}

void gdImageSetData (GDImage *image, GDByte *data, GDUInt size) {
    image->data = data;
    image->size = size;
}

