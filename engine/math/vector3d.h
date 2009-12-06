#ifndef _GDENGINE_VECTOR3D_H_
#define _GDENGINE_VECTOR3D_H_

#include <GDEngine/Types.h>

typedef struct {
    GDFloat x;
    GDFloat y;
    GDFloat z;
} GDVector3d;

void gdVector3dInit (GDVector3d *vector, GDFloat x, GDFloat y, GDFloat z);

void gdVector3dCopy (GDVector3d *dst, const GDVector3d *src);

GDFloat gdVector3dLength (const GDVector3d *vector);
GDFloat gdVector3dLengthSquared (const GDVector3d *vector);

GDFloat gdVector3dDistance (const GDVector3d *v1, const GDVector3d *v2);
GDFloat gdVector3dDistanceSquared (const GDVector3d *v1, const GDVector3d *v2);

void gdVector3dNegate (GDVector3d *result, const GDVector3d *vector);
void gdVector3dNormalized (GDVector3d *result, const GDVector3d *vector);

void gdVector3dAdd (GDVector3d *result,
                    const GDVector3d *v1,
                    const GDVector3d *v2);

void gdVector3dSubtract (GDVector3d *result,
                         const GDVector3d *v1,
                         const GDVector3d *v2);

void gdVector3dMultiply (GDVector3d *result, 
                         const GDVector3d *v1,
                         const GDVector3d *v2);

void gdVector3dMultiplyScalar (GDVector3d *result, 
                               const GDVector3d *vector,
                               GDFloat k);

void gdVector3dDivide (GDVector3d *result, 
                       const GDVector3d *v1,
                       const GDVector3d *v2);

void gdVector3dDivideScalar (GDVector3d *result, 
                             const GDVector3d *vector,
                             GDFloat k);

GDFloat gdVector3dDotProduct (const GDVector3d *v1, const GDVector3d *v2);

void gdVector3dCrossProduct (GDVector3d *result,
                             const GDVector3d *v1,
                             const GDVector3d *v2);

void gdVector3dLerp (GDVector3d *result, 
                     const GDVector3d *v1,
                     const GDVector3d *v2,
                     GDFloat amount);

#endif /* !_GDENGINE_VECTOR3D_H_ */

