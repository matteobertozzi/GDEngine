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

