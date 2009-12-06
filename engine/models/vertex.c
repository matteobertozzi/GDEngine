#include "vertex.h"

void gdVertexCopy (GDVertex *dst, const GDVertex *src) {
    gdVector3dCopy(&(dst->normal), &(src->normal));
    gdVector3dCopy(&(dst->coord), &(src->coord));
    gdVector2dCopy(&(dst->uv), &(src->uv));
}

