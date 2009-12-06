#include "vector3d.h"
#include "maths.h"

void gdVector3dInit (GDVector3d *vector, GDFloat x, GDFloat y, GDFloat z) {
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

void gdVector3dCopy (GDVector3d *dst, const GDVector3d *src) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

GDFloat gdVector3dLength (const GDVector3d *vector) {
    return(gdMathSqrt(gdVector3dLengthSquared(vector)));
}

GDFloat gdVector3dLengthSquared (const GDVector3d *vector) {
    return(gdMathPow2(vector->x) + 
           gdMathPow2(vector->y) +
           gdMathPow2(vector->z));
}

GDFloat gdVector3dDistance (const GDVector3d *v1, const GDVector3d *v2) {
    return(gdMathSqrt(gdVector3dDistanceSquared(v1, v2)));
}

GDFloat gdVector3dDistanceSquared (const GDVector3d *v1, const GDVector3d *v2) {
    return(((v1->x - v2->x) * (v1->x - v2->x)) +
           ((v1->y - v2->y) * (v1->y - v2->y)) +
           ((v1->z - v2->z) * (v1->z - v2->z)));
}

void gdVector3dNegate (GDVector3d *result, const GDVector3d *vector) {
    result->x = -(vector->x);
    result->y = -(vector->y);
    result->z = -(vector->z);
}

void gdVector3dNormalized (GDVector3d *result, const GDVector3d *vector) {
    GDVector3d zero;
    GDFloat factor;

    gdVector3dInit(&zero, 0.0f, 0.0f, 0.0f);
    factor = 1.0f / gdVector3dDistance(vector, &zero);
    result->x = vector->x * factor;
    result->y = vector->y * factor;
    result->z = vector->z * factor;
}

void gdVector3dAdd (GDVector3d *result,
                    const GDVector3d *v1,
                    const GDVector3d *v2)
{
    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;
}

void gdVector3dSubtract (GDVector3d *result,
                         const GDVector3d *v1,
                         const GDVector3d *v2)
{
    result->x = v1->x - v2->x;
    result->y = v1->y - v2->y;
    result->z = v1->z - v2->z;
}

void gdVector3dMultiply (GDVector3d *result, 
                         const GDVector3d *v1,
                         const GDVector3d *v2)
{
    result->x = v1->x * v2->x;
    result->y = v1->y * v2->y;
    result->z = v1->z * v2->z;
}

void gdVector3dMultiplyScalar (GDVector3d *result, 
                               const GDVector3d *vector,
                               GDFloat k)
{
    result->x = vector->x * k;
    result->y = vector->y * k;
    result->z = vector->z * k;
}

void gdVector3dDivide (GDVector3d *result, 
                       const GDVector3d *v1,
                       const GDVector3d *v2)
{
    result->x = v1->x / v2->x;
    result->y = v1->y / v2->y;
    result->z = v1->z / v2->z;
}

void gdVector3dDivideScalar (GDVector3d *result, 
                             const GDVector3d *vector,
                             GDFloat k)
{
    return(gdVector3dMultiplyScalar(result, vector, 1.0f / k));
}

GDFloat gdVector3dDotProduct (const GDVector3d *v1, const GDVector3d *v2) {
    return(v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

void gdVector3dCrossProduct (GDVector3d *result,
                             const GDVector3d *v1,
                             const GDVector3d *v2)
{
    GDVector3d r;

    r.x = v1->y * v2->z - v2->y * v1->z;
    r.y = -(v1->x * v2->z - v2->x * v1->z);
    r.z = v1->x * v2->y - v2->x * v1->y;

    gdVector3dCopy(result, &r);
}

void gdVector3dLerp (GDVector3d *result, 
                     const GDVector3d *v1,
                     const GDVector3d *v2,
                     GDFloat amount)
{
    result->x = gdMathLerp(v1->x, v2->x, amount);
    result->y = gdMathLerp(v1->y, v2->y, amount);
    result->z = gdMathLerp(v1->z, v2->z, amount);
}


