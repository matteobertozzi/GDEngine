#include <GDEngine/Config.h>

#if defined(GD_ENGINE_OPENGL_SUPPORT)

#include "opengl.h"
#include "macros.h"
#include "image.h"

static GDBool __initModelTexture (GDUInt index, void *data, void *args) {
    gdOpenGlInitTexture(gdImage(data));
    return(GD_FALSE);
}

GLuint gdOpenGlImageFormat (GDImageFormat format) {
    switch (format) {
        case GD_IMAGE_FORMAT_RGB:
            return(GL_RGB);
        case GD_IMAGE_FORMAT_RGBA:
            return(GL_RGBA);
        default:
            break;
    }

    return(0);
}

void gdOpenGlInitTexture (GDImage *image) {
    GLuint format;
    GLuint texId;

    gdReturnIfTrue(glIsTexture(image->id));

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    gdImageSetId(image, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); 

    format = gdOpenGlImageFormat(image->format);
    if (gdImageFormatIsCompressed(image->format)) {
        /* TODO: Handle Compression */
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, format,
                     image->width, image->height, 
                     0, format, GL_UNSIGNED_BYTE, image->data);
    }
}

void gdOpenGlInitModelTextures (GDModel *model) {
    GDUInt i;

    for (i = 0; i < model->nmeshes; ++i)
        gdListForeach(model->meshes[i].textures, __initModelTexture, NULL);
}

#endif /* GD_ENGINE_OPENGL_SUPPORT */

