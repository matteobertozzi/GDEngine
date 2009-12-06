#include "imagereader.h"
#include "modelreader.h"
#include "modelmesh.h"
#include "strings.h"
#include "model.h"
#include "debug.h"

typedef enum {
    GDT_STATE_SKIP,
    GDT_STATE_MODEL,
    GDT_STATE_BONES,
    GDT_STATE_MESH,
    GDT_STATE_TEXTURES,
    GDT_STATE_VERTICES,
    GDT_STATE_INDICES,
    GDT_STATE_VBONES,
    GDT_STATE_END_MESH,
    GDT_STATE_END_MODEL,
} GdtFormatState;

typedef struct {
    GdtFormatState state;
    char line[512];

    GDUInt meshIndex;
    GDUInt itemIndex;

    GDModelMesh *mesh;
    GDModel *model;
} GdtReadBuffer;

static GDBool __gdtParseTagVertices(GDModelReader *reader, GdtReadBuffer *rdbuf)
{
    GDUInt nvertices;
    sscanf(rdbuf->line, "VERTICES %u", &nvertices);
    if (!gdModelMeshInitVertices(rdbuf->mesh, nvertices))
        return(GD_FALSE);

    rdbuf->itemIndex = 0;
    return(GD_TRUE);
}

static GDBool __gdtParseTagIndices (GDModelReader *reader, GdtReadBuffer *rdbuf)
{
    GDUInt nindices;
    sscanf(rdbuf->line, "INDICES %u", &nindices);
    if (!gdModelMeshInitIndices(rdbuf->mesh, nindices))
        return(GD_FALSE);

    rdbuf->itemIndex = 0;
    return(GD_TRUE);
}

static GDBool __gdtParseTagVBones (GDModelReader *reader, GdtReadBuffer *rdbuf)
{
    GDUInt nvertices;
    sscanf(rdbuf->line, "VBONES %u", &nvertices);
    if (!gdModelMeshInitBones(rdbuf->mesh, nvertices))
        return(GD_FALSE);

    rdbuf->itemIndex = 0;
    return(GD_TRUE);
}

static GDBool __gdtParseTagBones (GDModelReader *reader, GdtReadBuffer *rdbuf) {
    GDUInt nbones;
    sscanf(rdbuf->line, "BONES %u", &nbones);
    if (!gdModelInitBones(rdbuf->model, nbones))
        return(GD_FALSE);

    rdbuf->itemIndex = 0;
    return(GD_TRUE);
}

static GDBool __gdtParseModel (GDModelReader *reader, GdtReadBuffer *rdbuf) {
    GDUInt nmeshes;

    if (!(rdbuf->model = gdModelAlloc()))
        return(GD_FALSE);

    sscanf(rdbuf->line, "MODEL %u %s", &nmeshes, rdbuf->line);
    if (!gdModelSetName(rdbuf->model, rdbuf->line))
        return(GD_FALSE);

    if (!gdModelInitMeshes(rdbuf->model, nmeshes))
        return(GD_FALSE);

    rdbuf->meshIndex = 0;
    return(GD_TRUE);
}

static GDBool __gdtParseBones (GDModelReader *reader, GdtReadBuffer *rdbuf) {
    GDFloat relX, relY, relZ;
    GDUInt parentId;
    char name[512];
    GDModelBone *b;
    int n;

    b = &(rdbuf->model->bones[rdbuf->itemIndex++]);
    n = sscanf(rdbuf->line, "%u %u %f %f %f %s", 
                             &(b->index), &parentId, 
                             &relX, &relY, &relZ,
                             name);

    /* Set Bone Name */
    if (n == 6)
        gdModelBoneSetName(b, name);

    /* Setup Relative Position */
    gdMatrixInitTranslation(&(b->transform), relX, relY, relZ);

    /* Setup Bone Parent */
    if (parentId == 0)
        b->parent = NULL;
    else
        b->parent = &(rdbuf->model->bones[parentId]);

    return(GD_TRUE);
}

static GDBool __gdtParseTextures (GDModelReader *reader, GdtReadBuffer *rdbuf) {
    GDImage *image;

    if ((image = gdImageReadFromFile(NULL, rdbuf->line)) != NULL)
        gdModelMeshAddTexture(rdbuf->mesh, image);

    return(GD_TRUE);
}

static GDBool __gdtParseMesh (GDModelReader *reader, GdtReadBuffer *rdbuf) {
    rdbuf->mesh = &(rdbuf->model->meshes[rdbuf->meshIndex++]);

    sscanf(rdbuf->line, "MESH %s", rdbuf->line);
    gdModelMeshSetName(rdbuf->mesh, rdbuf->line);

    return(GD_TRUE);
}

static GDBool __gdtParseVertices (GDModelReader *reader, GdtReadBuffer *rdbuf) {
    GDVertex *v;

    v = &(rdbuf->mesh->vertices[rdbuf->itemIndex++]);
    sscanf(rdbuf->line, "%f %f %f %f %f %f %f %f",
            &(v->coord.x), &(v->coord.y), &(v->coord.z),
            &(v->normal.x), &(v->normal.y), &(v->normal.z),
            &(v->uv.x), &(v->uv.y));

    return(GD_TRUE);
}

static GDBool __gdtParseIndices (GDModelReader *reader, GdtReadBuffer *rdbuf) {
    GDUInt idxs[6];
    int i, n;

    n = sscanf(rdbuf->line, "%u %u %u %u %u %u", 
                              idxs, idxs+1, idxs+2, idxs+3, idxs+4, idxs+5); 

    for (i = 0; i < n; ++i)
        rdbuf->mesh->indices[rdbuf->itemIndex++] = idxs[i];

    return(GD_TRUE);
}

static GDBool __gdtParseVBones (GDModelReader *reader, GdtReadBuffer *rdbuf) {
    GDFloat bWeights[4];
    GDUInt bIndices[4];
    GDUInt i, bCount;
    GDVertexBone *b;

    b = &(rdbuf->mesh->vbones[rdbuf->itemIndex++]);

    sscanf(rdbuf->line, "%u %u %u %u %f %f %f %f",
            bIndices, bIndices + 1, bIndices + 2, bIndices + 3,
            bWeights, bWeights + 1, bWeights + 2, bWeights + 3);

    /* Setup Vertex Bone */
    bCount = 0;
    for (i = 0; i < 4; ++i) {
        if (bWeights[i] != 0.0f)
            bCount++;
    }

    gdVertexBoneInit(b, bCount);
    for (i = 0, bCount = 0; i < 4; ++i) {
        if (bWeights[i] == 0.0f)
            continue;

        b->boneIndices[bCount] = bIndices[i];
        b->boneWeights[bCount] = bWeights[i];
        bCount++;
    }

    return(GD_TRUE);
}

static GDBool __gdtParseEndMesh (GDModelReader *reader, GdtReadBuffer *rdbuf) {
    return(GD_TRUE);
}

static GDBool __gdtParseEndModel (GDModelReader *reader, GdtReadBuffer *rdbuf) {
    if (rdbuf->model == NULL)
        return(GD_TRUE);

    /* Setup Bones, if are presents */
    if (rdbuf->model->bones != NULL)
        _gdModelBonesSetup(rdbuf->model->bones, rdbuf->model->nbones);

    if (!gdModelReaderAddModel(reader, rdbuf->model))
        return(GD_FALSE);

    return(GD_TRUE);
}

GDBool __gdReadModelGdt (GDModelReader *reader, const char *filename) {
    GDBool success = GD_FALSE;
    GdtReadBuffer rdbuf;
    FILE *fh;

    if ((fh = fopen(filename, "r")) == NULL) {
        gdWarningSysFail("fopen(%s)", filename);
        return(GD_FALSE);
    }

    rdbuf.state = GDT_STATE_SKIP;
    while (fgets(rdbuf.line, sizeof(rdbuf.line) - 1, fh) != NULL) {
        if (gdStringTrim(rdbuf.line) == NULL)
            continue;

        if (rdbuf.line[0] == '#')
            continue;

        if (!strncmp(rdbuf.line, "VERTICES", 8)) {
            rdbuf.state = GDT_STATE_VERTICES;
            __gdtParseTagVertices(reader, &rdbuf);
            continue;
        } else if (!strncmp(rdbuf.line, "INDICES", 7)) {
            rdbuf.state = GDT_STATE_INDICES;
            __gdtParseTagIndices(reader, &rdbuf);
            continue;
        } else if (!strncmp(rdbuf.line, "VBONES", 6)) {
            rdbuf.state = GDT_STATE_VBONES;
            __gdtParseTagVBones(reader, &rdbuf);
            continue;
        } else if (!strncmp(rdbuf.line, "TEXTURES", 8)) {
            rdbuf.state = GDT_STATE_TEXTURES;
            continue;
        } else if (!strncmp(rdbuf.line, "BONES", 5)) {            
            rdbuf.state = GDT_STATE_BONES;
            __gdtParseTagBones(reader, &rdbuf);
            continue;
        } else if (!strncmp(rdbuf.line, "MESH", 4)) {
            rdbuf.state = GDT_STATE_MESH;
        } else if (!strncmp(rdbuf.line, "END-MESH", 8)) {
            rdbuf.state = GDT_STATE_END_MESH;
        } else if (!strncmp(rdbuf.line, "MODEL", 5)) {
            rdbuf.state = GDT_STATE_MODEL;
        } else if (!strncmp(rdbuf.line, "END-MODEL", 9)) {
            rdbuf.state = GDT_STATE_END_MODEL;
        }

        switch (rdbuf.state) {
            case GDT_STATE_MODEL:
                if (!(success = __gdtParseModel(reader, &rdbuf)))
                    goto _exit_read_gdt;
                break;
            case GDT_STATE_BONES:
                if (!(success = __gdtParseBones(reader, &rdbuf)))
                    goto _exit_read_gdt;
                break;
            case GDT_STATE_MESH:
                if (!(success = __gdtParseMesh(reader, &rdbuf)))
                    goto _exit_read_gdt;
                break;
            case GDT_STATE_VERTICES:
                if (!(success = __gdtParseVertices(reader, &rdbuf)))
                    goto _exit_read_gdt;
                break;
            case GDT_STATE_INDICES:
                if (!(success = __gdtParseIndices(reader, &rdbuf)))
                    goto _exit_read_gdt;
                break;
            case GDT_STATE_VBONES:
                if (!(success = __gdtParseVBones(reader, &rdbuf)))
                    goto _exit_read_gdt;
                break;
            case GDT_STATE_TEXTURES:
                if (!(success = __gdtParseTextures(reader, &rdbuf)))
                    goto _exit_read_gdt;
                break;
            case GDT_STATE_END_MESH:
                if (!(success = __gdtParseEndMesh(reader, &rdbuf)))
                    goto _exit_read_gdt;
                break;
            case GDT_STATE_END_MODEL:
                if (!(success = __gdtParseEndModel(reader,& rdbuf)))
                    goto _exit_read_gdt;
                break;
            default:
                break;
        }
    }

_exit_read_gdt:
    fclose(fh);
    return(success);
}

