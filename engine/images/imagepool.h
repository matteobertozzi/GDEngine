#ifndef _GDENGINE_IMAGE_POOL_H_
#define _GDENGINE_IMAGE_POOL_H_

#include <GDEngine/Image.h>

GDImage *gdImagePoolFind (const char *filename);

GDImage *gdImagePoolAdd    (GDImage *image);
void     gdImagePoolRemove (GDImage *image);

#endif /* !_GDENGINE_IMAGE_POOL_H_ */

