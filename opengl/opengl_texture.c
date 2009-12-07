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

