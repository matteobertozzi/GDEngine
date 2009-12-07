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

