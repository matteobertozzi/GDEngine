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

#include "modelmesh.h"
#include "alloc.h"

GDModelMesh *gdModelMeshInit (GDModelMesh *mesh) {
    mesh->vbones = NULL;
    mesh->vertices = NULL;
    mesh->nvertices = 0;

    mesh->indices = NULL;
    mesh->nindices = 0;

    mesh->textures = gdListAlloc();

    mesh->name = NULL;
    return(mesh);
}

GDBool gdModelMeshInitVertices (GDModelMesh *mesh, 
                                GDUInt nvertices)
{
    if ((mesh->nvertices = nvertices) == 0) {
        mesh->vertices = NULL;
        mesh->vbones = NULL;
        return(GD_TRUE);    
    }

    if (!(mesh->vertices = gdAllocArray(GDVertex, nvertices)))
        return(GD_FALSE);

    return(GD_TRUE);
}

GDBool gdModelMeshInitIndices (GDModelMesh *mesh,
                               GDUInt nindices)
{
    if ((mesh->nindices = nindices) == 0) {
        mesh->indices = NULL;
        return(GD_TRUE);
    }

    if (!(mesh->indices = gdAllocArray(GDUInt, nindices)))
        return(GD_FALSE);

    return(GD_TRUE);
}

GDBool gdModelMeshInitBones (GDModelMesh *mesh, 
                             GDUInt nvertices)
{
    if (nvertices == 0)
        return(GD_FALSE);

    if (!(mesh->vbones = gdAllocArray(GDVertexBone, nvertices)))
        return(GD_FALSE);

    return(GD_TRUE);
}

/**
 * Release the Internal Structure of Model mesh.
 */
void gdModelMeshRelease (GDModelMesh *mesh) {
    GDUInt i;

    if (mesh->vbones != NULL) {
        for (i = 0; i < mesh->nvertices; ++i)
            gdVertexBoneRelease(&(mesh->vbones[i]));
        gdZFree(&(mesh->vbones));
    }

    if (mesh->vertices != NULL) {
        gdZFree(&(mesh->vertices));
        mesh->nvertices = 0;
    }

    if (mesh->indices != NULL) {
        gdZFree(&(mesh->indices));
        mesh->nindices = 0;
    }

    if (mesh->textures != NULL) {
        gdListRelease(mesh->textures, (GDReleaseFunc)gdImageRelease);
        mesh->textures = NULL;
    }

    if (mesh->name != NULL)
        gdZFree(&(mesh->name));
}

/**
 * Set specified name to the Model Mesh.
 */
GDBool gdModelMeshSetName (GDModelMesh *mesh, const char *name) {
    if (mesh->name != NULL)
        gdZFree(&(mesh->name));

    if (name == NULL)
        return(GD_TRUE);

    if (!(mesh->name = strdup(name)))
        return(GD_FALSE);

    return(GD_TRUE);
}

GDBool gdModelMeshAddTexture (GDModelMesh *mesh, GDImage *image) {
    return(gdListAppend(mesh->textures, image));
}

