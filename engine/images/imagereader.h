#ifndef _GDENGINE_IMAGE_READER_H_
#define _GDENGINE_IMAGE_READER_H_

#include <GDEngine/MipMap.h>
#include <GDEngine/Image.h>
#include <GDEngine/Types.h>

typedef GDUInt    (*GDMipMapCountFunc)     (FILE *fh);
typedef GDMipMap *(*GDMipMapReadFunc)      (GDMipMap *mipMap, FILE *fh);
typedef GDImage  *(*GDImageReadFunc)       (GDImage *image, FILE *fh);
typedef GDBool    (*GDImageIsFormatFunc)   (FILE *fh);

typedef struct {
    const char *        name;
    GDImageIsFormatFunc isFormat;
    GDMipMapCountFunc   mipMapCount;
    GDMipMapReadFunc    readMipMap;
    GDImageReadFunc     readImage;
} GDImagePlugin;

#define gdImagePlugin(p)        ((GDImagePlugin *)(p))

GDBool   gdImageReaderAddPlugin (GDImagePlugin *plugin);

GDImage *gdImageReadFromFile   (GDImage *image,
                                const char *filename);
GDImage *gdImageReadFromMipMap (GDImage *image,
                                GDMipMap *mipMap,
                                GDUInt level);
GDMipMap *gdMipMapReadFromFile  (GDMipMap *mipMap, 
                                 const char *filename);

#endif /* !_GDENGINE_IMAGE_READER_H_ */

