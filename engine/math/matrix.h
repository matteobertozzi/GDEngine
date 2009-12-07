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

#ifndef _GDENGINE_MATRIX_H_
#define _GDENGINE_MATRIX_H_

#include <GDEngine/Quaternion.h>
#include <GDEngine/Vector3d.h>
#include <GDEngine/Types.h>

typedef struct {
    GDFloat m11, m21, m31, m41;
    GDFloat m12, m22, m32, m42;
    GDFloat m13, m23, m33, m43;
    GDFloat m14, m24, m34, m44;
} GDMatrix;

#define gdMatrix(p)         ((GDMatrix *)(p))
#define gdMatrixFloat(p)    ((float *)(p))

void gdMatrixCopy            (GDMatrix *dst, const GDMatrix *src);

void gdMatrixInitIdentity    (GDMatrix *matrix);
void gdMatrixInitRotationX   (GDMatrix *matrix, GDFloat radians);
void gdMatrixInitRotationY   (GDMatrix *matrix, GDFloat radians);
void gdMatrixInitRotationZ   (GDMatrix *matrix, GDFloat radians);

void gdMatrixInitTranslation (GDMatrix *matrix, 
                              GDFloat x, GDFloat y, GDFloat z);

GDFloat gdMatrixTrace        (const GDMatrix *matrix);

void gdMatrixAdd             (GDMatrix *result,
                              const GDMatrix *m1,
                              const GDMatrix *m2);
void gdMatrixSubtract        (GDMatrix *result,
                              const GDMatrix *m1,
                              const GDMatrix *m2);

void gdMatrixMultiply        (GDMatrix *result, 
                              const GDMatrix *m1, 
                              const GDMatrix *m2);

void gdMatrixInverse         (GDMatrix *result, GDMatrix *matrix);
void gdMatrixTransposed      (GDMatrix *result, GDMatrix *matrix);

void gdMatrixRotateX         (GDMatrix *matrix, GDFloat radians);
void gdMatrixRotateY         (GDMatrix *matrix, GDFloat radians);
void gdMatrixRotateZ         (GDMatrix *matrix, GDFloat radians);

void gdMatrixTranslate       (GDMatrix *matrix,
                              GDFloat x, GDFloat y, GDFloat z);

void gdMatrixPrint           (GDMatrix *matrix);

void gdMatrixVector3dMultiply (GDVector3d *result, 
                               const GDVector3d *vector,
                               const GDMatrix *matrix);

void gdQuaternionInitFromMatrix (GDQuaternion *quaternion,
                                 const GDMatrix *matrix);

#endif /* !_GDENGINE_MATRIX_H_ */

