#include <GDEngine/Config.h>

#if defined(GD_ENGINE_OPENGL_SUPPORT)

#include "opengl.h"

void gdOpenGlSetCamera (GDCamera *camera) {
    glRotatef(camera->floor, 1.0f, 0.0f, 0.0f);
    glRotatef(360.0f - camera->yrotation, 0.0f, 1.0f, 0.0f);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

#endif /* GD_ENGINE_OPENGL_SUPPORT */

