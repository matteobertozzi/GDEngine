#include <GDEngine/Config.h>

#if defined(GD_ENGINE_OPENGL_SUPPORT)

#include "opengl.h"

#include "vector3d.h"
#include "alloc.h"

typedef void (*GDOpenGlDrawModelMesh) (GDModel *model, GDModelMesh *mesh);

static void __drawModelMesh (GDModel *model, 
                             GDModelMesh *mesh,
                             GDVertex *vertices)
{
    if (gdListSize(mesh->textures) > 0) {
        GDImage *texture;

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnable(GL_TEXTURE_2D);

        texture = gdImage(gdListAt(mesh->textures, gdListSize(mesh->textures) - 1));
        glBindTexture(GL_TEXTURE_2D, texture->id);

        glNormalPointer(GL_FLOAT, sizeof(GDVertex), gdVertexNormal(vertices));
        glTexCoordPointer(2, GL_FLOAT, sizeof(GDVertex), gdVertexUV(vertices));
        glVertexPointer(3, GL_FLOAT, sizeof(GDVertex), gdVertexCoord(vertices));
        glDrawElements(GL_TRIANGLES, mesh->nindices, GL_UNSIGNED_INT,mesh->indices);

        glDisable(GL_TEXTURE_2D);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    } else {
        glEnableClientState(GL_VERTEX_ARRAY);

        glVertexPointer(3, GL_FLOAT, sizeof(GDVertex), gdVertexCoord(vertices));
        glDrawElements(GL_TRIANGLES, mesh->nindices, GL_UNSIGNED_INT,mesh->indices);

        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

static void __drawSkeletalModelMesh (GDModel *model, GDModelMesh *mesh) {    
    GDVertex *vertices;
    GDMatrix boneMatrix;
    GDVector3d *v, *ov;
    GDModelBone *bone;
    GDVector3d p;
    GDUInt i, j;

    vertices = gdAllocArray(GDVertex, mesh->nvertices);

    for (i = 0; i < mesh->nvertices; ++i) {
        gdVertexCopy(&(vertices[i]), &(mesh->vertices[i]));
        ov = gdVertexCoord(&(mesh->vertices[i]));

        v = gdVertexCoord(&(vertices[i]));
        gdVector3dInit(v, 0.0f, 0.0f, 0.0f);

        for (j = 0; j < mesh->vbones[i].nbones; ++j) {
            bone = &(model->bones[mesh->vbones[i].boneIndices[j]]);
            gdModelBoneCalculateAbsPosition(bone, &boneMatrix);

            gdVector3dAdd(&p, ov, &(bone->_tdist));
            gdMatrixVector3dMultiply(&p, &p, &boneMatrix);

            gdVector3dMultiplyScalar(&p, &p, mesh->vbones[i].boneWeights[j]);
            gdVector3dAdd(v, v, &p);

            /* TODO: Fixme, Transform Normals */
        }
    }

    __drawModelMesh(model, mesh, vertices);

    gdFree(vertices);
}

static void __drawStaticModelMesh (GDModel *model, GDModelMesh *mesh) {
    __drawModelMesh(model, mesh, mesh->vertices);
}

#if defined(GD_ENGINE_DEBUG_BONES)
static void __drawBones (GDModelBone *bone) {
    GDMatrix matrix;
    GDVector3d b;

    glPushMatrix();

    gdModelBoneCalculateAbsPosition(bone, &matrix);
    gdVector3dInit(&b, 0.0f, 0.0f, 0.0f);
    gdMatrixVector3dMultiply(&b, &b, &matrix);

    if (bone->parent != NULL) {
        GDVector3d p;

        gdModelBoneCalculateAbsPosition(bone->parent, &matrix);
        gdVector3dInit(&p, 0.0f, 0.0f, 0.0f);
        gdMatrixVector3dMultiply(&p, &p, &matrix);

        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex3f(b.x, b.y, b.z);
        glVertex3f(p.x, p.y, p.z);
        glEnd();
    }

    glColor3f(0.0f, 1.0f, 0.0f);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex3f(b.x, b.y, b.z);
    glEnd();
    glPointSize(1.0);

    glPopMatrix();
}
#endif

void gdOpenGlModelDraw (GDModel *model) {
    GDOpenGlDrawModelMesh drawMesh;
    GDUInt i;

    if (gdModelIsStatic(model))
        drawMesh = __drawStaticModelMesh;
    else
        drawMesh = __drawSkeletalModelMesh;

    for (i = 0; i < model->nmeshes; ++i)
        drawMesh(model, &(model->meshes[i]));

#if defined(GD_ENGINE_DEBUG_BONES)
    /* Draw Bones */    
    for (i = 0; i < model->nbones; ++i)
        __drawBones(&(model->bones[i]));
#endif
}

#endif /* GD_ENGINE_OPENGL_SUPPORT */

