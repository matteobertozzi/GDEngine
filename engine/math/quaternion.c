#include "quaternion.h"
#include "maths.h"

void gdQuaternionInit (GDQuaternion *quaternion, 
                       GDFloat x, GDFloat y, GDFloat z, GDFloat w)
{
    quaternion->x = x;
    quaternion->y = y;
    quaternion->z = z;
    quaternion->w = w;
}

void gdQuaternionInitFromVector (GDQuaternion *quaternion, 
                                 const GDVector3d *vector,
                                 GDFloat scalar)
{
    quaternion->x = vector->x;
    quaternion->y = vector->y;
    quaternion->z = vector->z;
    quaternion->w = scalar;
}

void gdQuaternionInitFromAxisAngle (GDQuaternion *quaternion,
                                    const GDVector3d *axis,
                                    GDFloat radians)
{
    GDVector3d naxis;
    GDFloat fcos, fsin;

    gdVector3dNormalized(&naxis, axis);

    radians *= 0.5f;
    fcos = gdMathCos(radians);
    fsin = gdMathSin(radians);

    quaternion->x = axis->x * fsin;
    quaternion->y = axis->y * fsin;
    quaternion->z = axis->z * fsin;
    quaternion->w = fcos;

    gdQuaternionNormalized(quaternion, quaternion);
}

void gdQuaternionInitFromYawPitchRoll (GDQuaternion *quaternion,
                                       GDFloat yaw,
                                       GDFloat pitch,
                                       GDFloat roll)
{
    GDFloat atcos = gdMathCos(roll * 0.5f);
    GDFloat atsin = gdMathSin(roll * 0.5f);
    GDFloat leftcos = gdMathCos(pitch * 0.5f);
    GDFloat leftsin = gdMathSin(pitch * 0.5f);
    GDFloat upcos = gdMathCos(yaw * 0.5f);
    GDFloat upsin = gdMathSin(yaw * 0.5f);
    GDFloat atleftcos = atcos * leftcos;
    GDFloat atleftsin = atsin * leftsin;

    quaternion->x = atsin * leftcos * upcos + atcos * leftsin * upsin;
    quaternion->y = atcos * leftsin * upcos - atsin * leftcos * upsin;
    quaternion->z = atleftcos * upsin + atleftsin * upcos;
    quaternion->w = atleftcos * upcos - atleftsin * upsin;
}

void gdQuaternionCopy (GDQuaternion *dst, const GDQuaternion *src) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->w = src->w;
}

GDFloat gdQuaternionLength (const GDQuaternion *quaternion) {
    return(gdMathSqrt(gdQuaternionLengthSquared(quaternion)));
}

GDFloat gdQuaternionLengthSquared (const GDQuaternion *quaternion) {
    return(gdMathPow2(quaternion->x) + 
           gdMathPow2(quaternion->y) + 
           gdMathPow2(quaternion->z) +
           gdMathPow2(quaternion->w));
}


void gdQuaternionNegate (GDQuaternion *result, const GDQuaternion *quaternion) {
    result->x = -quaternion->x;
    result->y = -quaternion->y;
    result->z = -quaternion->z;
    result->w = -quaternion->w;
}

void gdQuaternionConjugate (GDQuaternion *result,
                            const GDQuaternion *quaternion)
{
    result->x = -quaternion->x;
    result->y = -quaternion->y;
    result->z = -quaternion->z;
    result->w = quaternion->w;
}

void gdQuaternionInverse (GDQuaternion *result,
                          const GDQuaternion *quaternion)
{
    GDFloat norm = gdQuaternionLengthSquared(quaternion);

    if (norm == 0.0f) {
        result->x = 0.0f;
        result->y = 0.0f;
        result->z = 0.0f;
        result->w = 0.0f;
    } else {
        norm = 1.0f / norm;

        gdQuaternionConjugate(result, quaternion);
        result->x *= norm;
        result->y *= norm;
        result->z *= norm;
        result->w *= norm;
    }
}

void gdQuaternionNormalized (GDQuaternion *result,
                             const GDQuaternion *quaternion)
{
    GDFloat mag = gdQuaternionLength(quaternion);

    if (mag > GD_MATH_EPSILON) {
        mag = 1.0f / mag;
        result->x = quaternion->x * mag;
        result->y = quaternion->y * mag;
        result->z = quaternion->z * mag;
        result->w = quaternion->w * mag;
    } else {
        result->x = 0.0f;
        result->y = 0.0f;
        result->z = 0.0f;
        result->w = 1.0f;
    }
}


void gdQuaternionAdd (GDQuaternion *result, 
                      const GDQuaternion *q1,
                      const GDQuaternion *q2)
{
    result->x = q1->x + q2->x;
    result->y = q1->y + q2->y;
    result->z = q1->z + q2->z;
    result->w = q1->w + q2->w;
}

void gdQuaternionSubtract (GDQuaternion *result, 
                           const GDQuaternion *q1,
                           const GDQuaternion *q2)
{
    result->x = q1->x - q2->x;
    result->y = q1->y - q2->y;
    result->z = q1->z - q2->z;
    result->w = q1->w - q2->w;
}

GDFloat gdQuaternionDotProduct (const GDQuaternion *q1,
                                    const GDQuaternion *q2)
{
    return((q1->x + q2->x)+(q1->y * q2->y)+(q1->z * q2->z)+(q1->w * q2->w));
}

void gdQuaternionMultiply (GDQuaternion *result, 
                           const GDQuaternion *q1,
                           const GDQuaternion *q2)
{
    result->x = (q1->w * q2->x)+(q1->x * q2->w)+(q1->y * q2->z)-(q1->z * q2->y);
    result->y = (q1->w * q2->y)-(q1->x * q2->z)+(q1->y * q2->w)+(q1->z * q2->x);
    result->z = (q1->w * q2->z)+(q1->x * q2->y)-(q1->y * q2->x)+(q1->z * q2->w);
    result->w = (q1->w * q2->w)-(q1->x * q2->x)-(q1->y * q2->y)-(q1->z * q2->z);
}

void gdQuaternionMultiplyScalar (GDQuaternion *result, 
                                 const GDQuaternion *quaternion,
                                 GDFloat scalar)
{
    result->x = quaternion->x * scalar;
    result->y = quaternion->y * scalar;
    result->z = quaternion->z * scalar;
    result->w = quaternion->w * scalar;
}

void gdQuaternionDivide (GDQuaternion *result, 
                         const GDQuaternion *q1,
                         const GDQuaternion *q2)
{
    GDFloat q2lensq = 1.0f / gdQuaternionLengthSquared(q2);
    GDFloat x2 = -q2->x * q2lensq;
    GDFloat y2 = -q2->y * q2lensq;
    GDFloat z2 = -q2->z * q2lensq;
    GDFloat w2 = -q2->w * q2lensq;

    result->x = (q1->x * w2) + (x2 * q1->w) + (q1->y * z2) - (q1->z * y2);
    result->y = (q1->y * w2) + (y2 * q1->w) + (q1->z * x2) - (q1->x * z2);
    result->z = (q1->z * w2) + (z2 * q1->w) + (q1->x * y2) - (q1->y * x2);
    result->w = (q1->w * w2) - ((q1->x * x2) + (q1->y * y2)) + (q1->z * z2);
}

void gdQuaternionDivideScalar (GDQuaternion *result, 
                               const GDQuaternion *quaternion,
                               GDFloat scalar)
{
    gdQuaternionMultiplyScalar(result, quaternion, 1.0f / scalar);
}

void gdQuaternionNLerp (GDQuaternion *result, 
                        const GDQuaternion *q1,
                        const GDQuaternion *q2,
                        GDFloat amount)
{
    GDFloat f2 = 1.0f - amount;
    GDFloat len;

    if (gdQuaternionDotProduct(q1, q2) >= 0.0f) {
        result->x = (f2 * q1->x) + (amount * q2->x);
        result->y = (f2 * q1->y) + (amount * q2->y);
        result->z = (f2 * q1->z) + (amount * q2->z);
        result->w = (f2 * q1->w) + (amount * q2->w);
    } else {
        result->x = (f2 * q1->x) - (amount * q2->x);
        result->y = (f2 * q1->y) - (amount * q2->y);
        result->z = (f2 * q1->z) - (amount * q2->z);
        result->w = (f2 * q1->w) - (amount * q2->w);
    }

    len = 1.0f / gdQuaternionLength(result);
    result->x *= len;
    result->y *= len;
    result->z *= len;
    result->w *= len;
}

void gdQuaternionSLerp (GDQuaternion *result, 
                        const GDQuaternion *q1,
                        const GDQuaternion *q2,
                        GDFloat amount)
{
    GDBool flag = GD_FALSE;
    GDFloat f2, f3;
    GDFloat dot;    

    if ((dot = gdQuaternionDotProduct(q1, q2)) < 0.0f) {
        flag = GD_TRUE;
        dot = -dot;
    }

    if (dot > 0.999999f) {
        f3 = 1.0f - amount;
        f2 = flag ? -amount : amount;
    } else {
        GDFloat angle = gdMathAcos(dot);
        GDFloat sina = 1.0f / gdMathSin(angle);

        f3 = gdMathSin((1.0f - amount) * angle) * sina;

        if (flag)
            f2 = -gdMathSin(amount * angle) * sina;
        else
            f2 = gdMathSin(amount * angle) * sina;
    }

    result->x = (f3 * q1->x) + (f2 * q2->x);
    result->y = (f3 * q1->y) + (f2 * q2->y);
    result->z = (f3 * q1->z) + (f2 * q2->z);
    result->w = (f3 * q1->w) + (f2 * q2->w);
}

