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

#ifndef _GDENGINE_OPENGL_H_
#define _GDENGINE_OPENGL_H_

#include <GDEngine/Config.h>

#if defined(GD_ENGINE_OPENGL_SUPPORT)

#if defined(__APPLE__)
    #include <GLUT/glut.h>
	#include <OpenGL/glu.h>
    #include <OpenGL/gl.h>
#else
    #include <GL/glut.h>
    #include <GL/glu.h>
    #include <GL/gl.h>
#endif

#include <GDEngine/Camera.h>
#include <GDEngine/Model.h>
#include <GDEngine/Image.h>

void    gdOpenGlSetCamera         (GDCamera *camera);

void    gdOpenGlModelDraw         (GDModel *model);

GLuint  gdOpenGlImageFormat       (GDImageFormat format);
void    gdOpenGlInitTexture       (GDImage *image);
void    gdOpenGlInitModelTextures (GDModel *model);

void    gdOpenGlDrawString        (GLfloat x, GLfloat y, const char *text);

#endif /* GD_ENGINE_OPENGL_SUPPORT */
#endif /* !_GDENGINE_OPENGL_H_ */

