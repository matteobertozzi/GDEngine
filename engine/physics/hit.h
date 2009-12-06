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

