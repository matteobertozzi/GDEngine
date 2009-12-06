#ifndef _GDENGINE_MODEL_BONE_H_
#define _GDENGINE_MODEL_BONE_H_

#include <GDEngine/Vector3d.h>
#include <GDEngine/Matrix.h>

typedef struct _GDModelBone {
    GDMatrix transform;
    GDVector3d _tdist;

    struct _GDModelBone *parent;
    struct _GDModelBone **children;
    GDUInt nchildren;

    GDUInt index;
    char *name;
} GDModelBone;

void _gdModelBonesSetup (GDModelBone *bones, GDUInt n);

GDModelBone *gdModelBoneInit    (GDModelBone *bone);
void         gdModelBoneRelease (GDModelBone *bone);

void         gdModelBoneSetName (GDModelBone *bone, const char *name);

void gdModelBoneCalculateAbsPosition (GDModelBone *bone, GDMatrix *matrix);
void gdModelBoneCalculateAbsParentPosition (GDModelBone *bone, GDMatrix *matrix);

void gdModelBoneDebug (GDModelBone *root);

#endif /* !_GDENGINE_MODEL_BONE_H_ */

