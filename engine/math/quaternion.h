#ifndef _GDENGINE_QUATERNION_H_
#define _GDENGINE_QUATERNION_H_

#include <GDEngine/Vector3d.h>
#include <GDEngine/Types.h>

typedef struct {
    GDFloat x;
    GDFloat y;
    GDFloat z;
    GDFloat w;
} GDQuaternion;

void gdQuaternionInit (GDQuaternion *quaternion, 
                       GDFloat x, GDFloat y, GDFloat z, GDFloat w);
void gdQuaternionInitFromVector (GDQuaternion *quaternion, 
                                 const GDVector3d *vector,
                                 GDFloat scalar);
void gdQuaternionInitFromAxisAngle (GDQuaternion *quaternion,
                                    const GDVector3d *axis,
                                    GDFloat radians);
void gdQuaternionInitFromYawPitchRoll (GDQuaternion *quaternion,
                                       GDFloat yaw,
                                       GDFloat pitch,
                                       GDFloat roll);

void gdQuaternionCopy (GDQuaternion *dst, const GDQuaternion *src); 

GDFloat gdQuaternionLength (const GDQuaternion *quaternion);
GDFloat gdQuaternionLengthSquared (const GDQuaternion *quaternion);

void gdQuaternionNegate (GDQuaternion *result, const GDQuaternion *quaternion);
void gdQuaternionConjugate (GDQuaternion *result,
                            const GDQuaternion *quaternion);
void gdQuaternionInverse (GDQuaternion *result,
                          const GDQuaternion *quaternion);
void gdQuaternionNormalized (GDQuaternion *result,
                             const GDQuaternion *quaternion);

void gdQuaternionAdd (GDQuaternion *result, 
                      const GDQuaternion *q1,
                      const GDQuaternion *q2);
void gdQuaternionSubtract (GDQuaternion *result, 
                           const GDQuaternion *q1,
                           const GDQuaternion *q2);
GDFloat glDataQuaternionDotProduct (const GDQuaternion *q1,
                                    const GDQuaternion *q2);
void gdQuaternionMultiply (GDQuaternion *result, 
                           const GDQuaternion *q1,
                           const GDQuaternion *q2);
void gdQuaternionMultiplyScalar (GDQuaternion *result, 
                                 const GDQuaternion *quaternion,
                                 GDFloat scalar);
void gdQuaternionDivide (GDQuaternion *result, 
                         const GDQuaternion *q1,
                         const GDQuaternion *q2);
void gdQuaternionDivideScalar (GDQuaternion *result, 
                               const GDQuaternion *quaternion,
                               GDFloat scalar);

void gdQuaternionNLerp (GDQuaternion *result, 
                        const GDQuaternion *q1,
                        const GDQuaternion *q2,
                        GDFloat amount);
void gdQuaternionSLerp (GDQuaternion *result, 
                        const GDQuaternion *q1,
                        const GDQuaternion *q2,
                        GDFloat amount);

#endif /* !_GDENGINE_QUATERNION_H_ */

