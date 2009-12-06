#ifndef _GDENGINE_MODEL_MESH_H_
#define _GDENGINE_MODEL_MESH_H_

#include <GDEngine/VertexBone.h>
#include <GDEngine/Vertex.h>
#include <GDEngine/Image.h>
#include <GDEngine/List.h>

typedef struct {
    GDVertexBone *vbones;
    GDVertex *vertices;
    GDUInt nvertices;

    GDUInt *indices;
    GDUInt nindices;

    GDList *textures;

    char *name;
} GDModelMesh;

GDModelMesh *gdModelMeshInit    (GDModelMesh *mesh);

GDBool gdModelMeshInitVertices  (GDModelMesh *mesh, GDUInt nvertices);
GDBool gdModelMeshInitIndices   (GDModelMesh *mesh, GDUInt nindices);
GDBool gdModelMeshInitBones     (GDModelMesh *mesh, GDUInt nvertices);
void   gdModelMeshRelease       (GDModelMesh *mesh);

GDBool gdModelMeshSetName       (GDModelMesh *mesh, const char *name);
GDBool gdModelMeshAddTexture    (GDModelMesh *mesh, GDImage *image);

#endif /* !_GDENGINE_MODEL_MESH_H_ */

