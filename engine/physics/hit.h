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

#ifndef _GDENGINE_HIT_H_
#define _GDENGINE_HIT_H_

#include <GDEngine/Geometry.h>
#include <GDEngine/Types.h>

typedef enum {
    GD_HIT_TYPE_DISJOINT,
    GD_HIT_TYPE_INTERSECTS,
    GD_HIT_TYPE_CONTAINS
} GDHitType;

typedef enum {
    GD_HIT_OBJECT_TYPE_BOX,
    GD_HIT_OBJECT_TYPE_SPHERE,
} GDHitObjectType;

typedef struct {
    union {
        GDBox box;
        GDSphere sphere;
    } shape;
    GDHitObjectType type;
} GDHitObject;

#define gdHitBox(p)             (&((p)->shape.box))
#define gdHitSphere(p)          (&((p)->shape.sphere))
#define gdHitObjectIsBox(p)     ((p)->type == GD_HIT_OBJECT_TYPE_BOX)
#define gdHitObjectIsSphere(p)  ((p)->type == GD_HIT_OBJECT_TYPE_SPHERE)

#define gdHitSetBoxType(p)      ((p)->type = GD_HIT_OBJECT_TYPE_BOX)
#define gdHitSetSphereType(p)   ((p)->type = GD_HIT_OBJECT_TYPE_SPHERE)

GDBool gdHitDisjoint     (GDHitObject *obj1, GDHitObject *obj2);
GDBool gdHitContains     (GDHitObject *obj1, GDHitObject *obj2);
GDBool gdHitCollision    (GDHitObject *obj1, GDHitObject *obj2);
GDBool gdHitIntersects   (GDHitObject *obj1, GDHitObject *obj2);

GDHitType gdHitInfo      (GDHitObject *obj1, GDHitObject *obj2);
GDHitType gdHitPointInfo (GDHitObject *obj, GDVector3d *point);

#endif /* !_GDENGINE_HIT_H_ */

