#ifndef _GLDATAENGINE_GEOMETRY_H_
#define _GLDATAENGINE_GEOMETRY_H_

#include <GDEngine/Vector3d.h>
#include <GDEngine/Types.h>

typedef struct {
    GDVector3d min;
    GDVector3d max;
} GDBox;

typedef struct {
    GDVector3d center;
    GDFloat radius;
} GDSphere;

#endif /* !_GLDATAENGINE_GEOMETRY_H_ */

