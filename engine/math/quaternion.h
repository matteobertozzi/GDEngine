/*
 * Copyright (c) 2009, Matteo Bertozzi <theo.bertozzi@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Matteo Bertozzi nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Matteo Bertozzi ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Matteo Bertozzi BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

