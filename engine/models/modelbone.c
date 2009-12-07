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

#include "modelbone.h"
#include "alloc.h"

static void __modelBoneSetupParents (GDModelBone *bones, GDUInt n) {
    GDModelBone *bone;
    GDUInt i;

    /* Reset Number of Children */
    for (i = 0; i < n; ++i)
        bones[i].nchildren = 0;
    
    /* Set number of child per Bone */
    for (i = 0; i < n; ++i) {
        bone = &(bones[i]);
        
        if (bone->parent != NULL)
            bone->parent->nchildren++;
    }
    
    /* Alloc Children */
    for (i = 0; i < n; ++i) {
        bone = &(bones[i]);
        
        if (bone->nchildren < 1) {
            bone->children = NULL;
            continue;
        }
        
        bone->children = gdAllocArray(GDModelBone *, bone->nchildren);
    }
}

static void __modelBoneSetupChildren (GDModelBone *bones, GDUInt n) {
    GDModelBone *bone;
    GDUInt *childs;
    GDUInt idx;
    GDUInt i;

    childs = gdZAllocArray(GDUInt, n);
    
    for (i = 0; i < n; ++i) {
        bone = &(bones[i]);
        if (bone->parent != NULL) {
            idx = childs[bone->parent->index]++;
            bone->parent->children[idx] = bone;
        }
    }

    gdFree(childs);
}

static void __modelBoneSetupZDist (GDModelBone *bones, GDUInt n) {
    GDMatrix matrix;
    GDVector3d zero;
    GDVector3d pos;
    GDUInt i;

    gdVector3dInit(&zero, 0.0f, 0.0f, 0.0f);
    for (i = 0; i < n; ++i) {
        gdModelBoneCalculateAbsPosition(&bones[i], &matrix);
        gdMatrixVector3dMultiply(&pos, &zero, &matrix);
        gdVector3dSubtract(&(bones[i]._tdist), &zero, &pos);
    }
}

void _gdModelBonesSetup (GDModelBone *bones, GDUInt n) {
    /* Setup Parents and Children */
    __modelBoneSetupParents(bones, n);
    __modelBoneSetupChildren(bones, n);

    /* Setup Z-Dist, for Drawing Translation */
    __modelBoneSetupZDist(bones, n);

#if 0
    gdModelBoneDebug(&(bones[1]));
#endif
}

GDModelBone *gdModelBoneInit (GDModelBone *bone) {
    bone->parent = NULL;
    bone->children = NULL;
    bone->nchildren = 0;

    bone->index = 0;
    bone->name = NULL;
    return(bone);
}

void gdModelBoneRelease (GDModelBone *bone) {
    if (bone->name != NULL)
        gdZFree(&(bone->name));
}

void gdModelBoneSetName (GDModelBone *bone, const char *name) {
    if (bone->name != NULL)
        gdZFree(&(bone->name));

    if (name == NULL)
        return;

    bone->name = strdup(name);
}

void gdModelBoneCalculateAbsParentPosition (GDModelBone *bone, GDMatrix *matrix)
{
    if (bone->parent == NULL)
        gdMatrixInitIdentity(matrix);
    else
        gdModelBoneCalculateAbsPosition(bone->parent, matrix);
}

void gdModelBoneCalculateAbsPosition (GDModelBone *bone, GDMatrix *matrix) {
    if (bone->parent == NULL) {
        gdMatrixCopy(matrix, &(bone->transform));
    } else {
        gdModelBoneCalculateAbsPosition(bone->parent, matrix);
        gdMatrixMultiply(matrix, &(bone->transform), matrix);
    }
}

static void __printTabs (GDUInt level) {
    while (level--)
        printf(" ");
}

static void __debugBone (GDModelBone *bone, GDUInt level) {
    GDUInt i;
    
    __printTabs(level); printf("BONE ID: %u\n", bone->index);
    if (bone->parent != NULL) {
        __printTabs(level); printf(" - PARENT: %u\n", bone->parent->index);
    }

    __printTabs(level); printf(" - CHILDS: %u\n", bone->nchildren);
    for (i = 0; i < bone->nchildren; ++i)
        __debugBone(bone->children[i], level + 1);
}

void gdModelBoneDebug (GDModelBone *root) {
    __debugBone(root, 0);
}

