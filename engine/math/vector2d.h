#ifndef _GDENGINE_VECTOR2D_H_
#define _GDENGINE_VECTOR2D_H_

#include <GDEngine/Types.h>

typedef struct {
    GDFloat x;
    GDFloat y;
} GDVector2d;

void gdVector2dCopy (GDVector2d *dst, const GDVector2d *src);

#endif /* !_GDENGINE_VECTOR2D_H_ */

