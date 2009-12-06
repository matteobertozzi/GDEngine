#include "model.h"
#include "alloc.h"

GDModel *gdModelAlloc (void) {
    GDModel *model;

    model = gdAlloc(GDModel);
    model->meshes = NULL;
    model->bones = NULL;
    model->root = NULL;
    model->name = NULL;
    model->nmeshes = 0;

    return(model);
}

void gdModelRelease (GDModel *model) {
    GDUInt i;

    if (model->bones != NULL) {
        for (i = 0; i < model->nbones; ++i)
            gdModelBoneRelease(&(model->bones[i]));

        gdZFree(&(model->bones));
        model->root = NULL;
        model->nbones = 0;
    }

    if (model->meshes != NULL) {
        for (i = 0; i < model->nmeshes; ++i)
            gdModelMeshRelease(&(model->meshes[i]));

        gdZFree(&(model->meshes));
        model->nmeshes = 0;
    }

    if (model->name != NULL)
        gdZFree(&(model->name));
}

GDBool gdModelInitBones (GDModel *model, GDUInt nbones) {
    GDUInt i;

    if ((model->nbones = nbones) == 0) {
        model->bones = NULL;
        return(GD_TRUE);
    }

    if (!(model->bones = gdAllocArray(GDModelBone, nbones)))
        return(GD_FALSE);

    model->root = &(model->bones[0]);

    for (i = 0; i < nbones; ++i)
        gdModelBoneInit(&(model->bones[i]));

    return(GD_TRUE);
}

GDBool gdModelInitMeshes (GDModel *model, GDUInt nmeshes) {
    GDUInt i;

    if ((model->nmeshes = nmeshes) == 0) {
        model->meshes = NULL;
        model->nmeshes = 0;
        return(GD_TRUE);
    }

    if (!(model->meshes = gdZAllocArray(GDModelMesh, nmeshes)))
        return(GD_FALSE);

    for (i = 0; i < nmeshes; ++i)
        gdModelMeshInit(&(model->meshes[i]));

    return(GD_TRUE);
}

GDBool gdModelSetName (GDModel *model, const char *name) {
    if (model->name != NULL)
        gdZFree(&(model->name));

    if (name == NULL)
        return(GD_TRUE);

    if (!(model->name = strdup(name)))
        return(GD_FALSE);

    return(GD_TRUE);
}

