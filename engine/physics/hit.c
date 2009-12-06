#include "maths.h"
#include "hit.h"

static GDHitType __boxContainsBox (GDBox *box1, GDBox *box2) {
    if (box2->max.x < box1->min.x || box2->min.x > box1->max.x ||
        box2->max.y < box1->min.y || box2->min.y > box1->max.y ||
        box2->max.z < box1->min.z || box2->min.z > box1->max.z)
    {
        return(GD_HIT_TYPE_DISJOINT);
    }

    if (box2->min.x >= box1->min.x && box2->max.x <= box1->max.x &&
        box2->min.y >= box1->min.y && box2->max.y <= box1->max.y &&
        box2->min.z >= box1->min.z && box2->max.z <= box1->max.z)
    {
        return(GD_HIT_TYPE_CONTAINS);
    }

    return(GD_HIT_TYPE_INTERSECTS);
}

static GDHitType __boxContainsSphere (GDBox *box, GDSphere *sphere)
{
    GDFloat d = 0.0f;

    if ((sphere->center.x - box->min.x) > sphere->radius &&
        (sphere->center.y - box->min.y) > sphere->radius &&
        (sphere->center.z - box->min.z) > sphere->radius &&
        (box->max.x - sphere->center.x) > sphere->radius &&
        (box->max.y - sphere->center.y) > sphere->radius &&
        (box->max.z - sphere->center.z) > sphere->radius)
    {
        return(GD_HIT_TYPE_CONTAINS);
    }

    if ((sphere->center.x - box->min.x) <= sphere->radius)
        d += gdPow2(sphere->center.x - box->min.x);
    else if ((box->max.x - sphere->center.x) <= sphere->radius)
        d += gdPow2(sphere->center.x - box->max.x);

    if ((sphere->center.y - box->min.y) <= sphere->radius)
        d += gdPow2(sphere->center.y - box->min.y);
    else if ((box->max.y - sphere->center.y) <= sphere->radius)
        d += gdPow2(sphere->center.y - box->max.y);

    if ((sphere->center.z - box->min.z) <= sphere->radius)
        d += gdPow2(sphere->center.z - box->min.z);
    else if ((box->max.z - sphere->center.z) <= sphere->radius)
        d += gdPow2(sphere->center.z - box->max.z);

    if (d <= gdPow2(sphere->radius))
        return(GD_HIT_TYPE_INTERSECTS);

    return(GD_HIT_TYPE_DISJOINT);
}

static GDHitType __boxContainsPoint (GDBox *box, GDVector3d *point) 
{
    if (point->x < box->min.x || point->x > box->max.x ||
        point->y < box->min.y || point->y > box->max.y ||
        point->z < box->min.z || point->z > box->max.z)
    {
        return(GD_HIT_TYPE_DISJOINT);
    }

    if (point->x == box->min.x || point->x == box->max.x ||
        point->y == box->min.y || point->y == box->max.y ||
        point->z == box->min.z || point->z == box->max.z)
    {
        return(GD_HIT_TYPE_INTERSECTS);
    }

    return(GD_HIT_TYPE_CONTAINS);
}

static GDHitType __sphereContainsPoint (GDSphere *sphere, GDVector3d *point)
{
    GDFloat distance;

    distance = gdVector3dDistance(point, &(sphere->center));

    if (distance > sphere->radius)
        return(GD_HIT_TYPE_DISJOINT);

    if (distance < sphere->radius)
        return(GD_HIT_TYPE_CONTAINS);

    return(GD_HIT_TYPE_INTERSECTS);
}

static GDHitType __sphereContainsBox (GDSphere *sphere, GDBox *box)
{
    GDVector3d boxCorners[8];
    GDFloat d = 0.0f;
    GDUInt i;

    gdVector3dInit(&(boxCorners[0]), box->min.x, box->max.y, box->max.z);
    gdVector3dInit(&(boxCorners[1]), box->max.x, box->max.y, box->max.z);
    gdVector3dInit(&(boxCorners[2]), box->max.x, box->min.y, box->max.z);
    gdVector3dInit(&(boxCorners[3]), box->min.x, box->min.y, box->max.z);
    gdVector3dInit(&(boxCorners[4]), box->min.x, box->max.y, box->min.z);
    gdVector3dInit(&(boxCorners[5]), box->max.x, box->max.y, box->min.z);
    gdVector3dInit(&(boxCorners[6]), box->max.x, box->min.y, box->min.z);
    gdVector3dInit(&(boxCorners[7]), box->min.x, box->min.y, box->min.z);

    for (i = 0; i < 8; ++i) {
        if (__sphereContainsPoint(sphere, &boxCorners[i]) == GD_HIT_TYPE_DISJOINT)
            goto __sphere_box_not_inside;
    }

    return(GD_HIT_TYPE_CONTAINS);

__sphere_box_not_inside:
    if (sphere->center.x < box->min.x)
        d += gdPow2(sphere->center.x - box->min.x);
    else if (sphere->center.x > box->max.x)
        d += gdPow2(sphere->center.x - box->max.x);

    if (sphere->center.y < box->min.y)
        d += gdPow2(sphere->center.y - box->min.y);
    else if (sphere->center.y > box->max.y)
        d += gdPow2(sphere->center.y - box->max.y);

    if (sphere->center.z < box->min.z)
        d += gdPow2(sphere->center.z - box->min.z);
    else if (sphere->center.y > box->max.y)
        d += gdPow2(sphere->center.z - box->max.z);

    if (d <= gdPow2(sphere->radius))
        return(GD_HIT_TYPE_INTERSECTS);

    return(GD_HIT_TYPE_DISJOINT);
}

static GDHitType __sphereContainsSphere (GDSphere *s1, GDSphere *s2)
{
    GDFloat distance;

    distance = gdVector3dDistance(&(s2->center), &(s1->center));

    if (distance > (s2->radius + s1->radius))
        return(GD_HIT_TYPE_DISJOINT);

    if (distance <= (s1->radius - s2->radius))
        return(GD_HIT_TYPE_CONTAINS);

    return(GD_HIT_TYPE_INTERSECTS);
}


GDBool gdHitDisjoint (GDHitObject *obj1, GDHitObject *obj2) {
    return(gdHitInfo(obj1, obj2) == GD_HIT_TYPE_DISJOINT);
}

GDBool gdHitContains (GDHitObject *obj1, GDHitObject *obj2) {
    return(gdHitInfo(obj1, obj2) == GD_HIT_TYPE_CONTAINS);
}

GDBool gdHitCollision (GDHitObject *obj1, GDHitObject *obj2) {
    return(gdHitInfo(obj1, obj2) != GD_HIT_TYPE_DISJOINT);
}

GDBool gdHitIntersects (GDHitObject *obj1, GDHitObject *obj2) {
    return(gdHitInfo(obj1, obj2) == GD_HIT_TYPE_INTERSECTS);
}

GDHitType gdHitInfo (GDHitObject *obj1, GDHitObject *obj2) {
    if (gdHitObjectIsBox(obj1)) {
        if (gdHitObjectIsBox(obj2))
            return(__boxContainsBox(gdHitBox(obj1), gdHitBox(obj2)));
        /* else if (gdHitObjectIsSphere(obj2)) */
        return(__boxContainsSphere(gdHitBox(obj1), gdHitSphere(obj2)));
        /* ... more types ... */
    } 

    if (gdHitObjectIsSphere(obj1)) {
        if (gdHitObjectIsBox(obj2))
            return(__sphereContainsBox(gdHitSphere(obj1), gdHitBox(obj2)));
        /* else if (gdHitObjectIsSphere(obj2)) */
        return(__sphereContainsSphere(gdHitSphere(obj1), gdHitSphere(obj2)));
        /* ... more types ... */
    }

    /* Unreached... */
    return(GD_HIT_TYPE_DISJOINT);
}

GDHitType gdHitPointInfo (GDHitObject *obj, GDVector3d *point) {
    if (gdHitObjectIsBox(obj))
        return(__boxContainsPoint(gdHitBox(obj), point));
    
    if (gdHitObjectIsSphere(obj))
        return(__sphereContainsPoint(gdHitSphere(obj), point));

    /* Unreached... */
    return(GD_HIT_TYPE_DISJOINT);
}

