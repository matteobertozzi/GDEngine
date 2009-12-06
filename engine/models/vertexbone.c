#include "vertexbone.h"
#include "alloc.h"

/**
 * Initialize Vertex Bone Internal Structure with specified number of bones.
 */
GDBool gdVertexBoneInit (GDVertexBone *vbone, GDUInt nbones) {
    if ((vbone->nbones = nbones) == 0) {
        vbone->boneIndices = NULL;
        vbone->boneWeights = NULL;
        return(GD_TRUE);
    }

    if (!(vbone->boneIndices = gdAllocArray(GDUInt, nbones)))
        return(GD_FALSE);

    if (!(vbone->boneWeights = gdAllocArray(GDFloat, nbones)))
        goto _failed_free_indices;

    return(GD_TRUE);

_failed_free_indices:
    gdFree(vbone->boneIndices);
    return(GD_FALSE);
}

void gdVertexBoneRelease (GDVertexBone *vbone) {
    if (vbone->boneIndices != NULL)
        gdZFree(&(vbone->boneIndices));

    if (vbone->boneWeights != NULL)
        gdZFree(&(vbone->boneWeights));

    vbone->nbones = 0;
}

