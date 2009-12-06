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

