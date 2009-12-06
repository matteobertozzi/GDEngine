#ifndef _GDENGINE_VERTEX_H_
#define _GDENGINE_VERTEX_H_

#include <GDEngine/Vector3d.h>
#include <GDEngine/Vector2d.h>

typedef struct {
    GDVector3d coord;
    GDVector3d normal;
    GDVector2d uv;
} GDVertex;

#define gdVertex(p)             ((GDVertex *)(p))
#define gdVertexCoord(p)        (&((p)->coord))
#define gdVertexNormal(p)       (&((p)->normal))
#define gdVertexUV(p)           (&((p)->uv))

void gdVertexCopy (GDVertex *dst, const GDVertex *src);

#endif /* !_GDENGINE_VERTEX_H_ */

