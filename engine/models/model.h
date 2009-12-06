#ifndef _GDENGINE_MODEL_H_
#define _GDENGINE_MODEL_H_

#include <GDEngine/ModelBone.h>
#include <GDEngine/ModelMesh.h>

typedef struct {
    GDModelMesh *meshes;
    GDUInt nmeshes;

    GDModelBone *bones;
    GDModelBone *root;
    GDUInt nbones;

    char *name;
} GDModel;

#define gdModel(p)          ((GDModel *)(p))

#define gdModelIsStatic(p)  ((p)->bones == NULL)

GDModel *gdModelAlloc       (void);
void     gdModelRelease     (GDModel *model);

GDBool gdModelInitBones     (GDModel *model,
                             GDUInt nbones);

GDBool gdModelInitMeshes    (GDModel *model,
                             GDUInt nmeshes);

GDBool gdModelSetName       (GDModel *model,
                             const char *name);

#endif /* !_GDENGINE_MODEL_H_ */

