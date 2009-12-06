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

