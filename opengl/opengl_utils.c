#include <GDEngine/Config.h>

#if defined(GD_ENGINE_OPENGL_SUPPORT)

#include "opengl.h"

void gdOpenGlDrawString (GLfloat x, GLfloat y, const char *text) {
    const char *p;

	glRasterPos2f(x, y);
    for (p = text; *p != '\0'; ++p)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p);
}

#endif /* GD_ENGINE_OPENGL_SUPPORT */

