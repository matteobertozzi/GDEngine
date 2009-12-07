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

