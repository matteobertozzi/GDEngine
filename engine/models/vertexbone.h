#ifndef _GDENGINE_VERTEX_BONE_H_
#define _GDENGINE_VERTEX_BONE_H_

#include <GDEngine/Types.h>

typedef struct {
    GDFloat *boneWeights;
    GDUInt *boneIndices;
    GDUInt nbones;
} GDVertexBone;

GDBool gdVertexBoneInit    (GDVertexBone *vbone, GDUInt nbones);
void   gdVertexBoneRelease (GDVertexBone *vbone);

#endif /* !_GDENGINE_VERTEX_BONE_H_ */

