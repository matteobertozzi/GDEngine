#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GDEngine/OpenGL.h>

#include <GDEngine/ImageReader.h>
#include <GDEngine/Maths.h>
#include <GDEngine/Hit.h>

#define ANIMATION_TIMEOUT       (100)
static GLfloat __sphere_x = 0.0f;

/* Objects Bounding Box (Hit Objects) */
GDHitObject __cube_right;
GDHitObject __cube_left;
GDHitObject __sphere;

/* Texture and Display List */
static GLuint __texture_id_crate;
static GLuint __sphere_id;
static GLuint __cube_id;

static void setupTexture (void) {
    GDImage image;

    gdImageInit(&image);
    if (gdImageReadFromFile(&image, "examples/opengl/images/crate.bmp")) {
        gdOpenGlInitTexture(&image);
        __texture_id_crate = image.id;

        gdImageRelease(&image);
    }
}

static void drawSphere (void) {
    glutWireSphere(0.8, 8, 8);
}

static void drawCube (void) {
    GLshort vertices[] = {
        /* x  y  z     u  v */
         1,  1, -1,    0, 1, 
         1, -1, -1,    1, 1, 
        -1, -1, -1,    1, 0, 
        -1,  1, -1,    0, 0, 
         1,  1,  1,    0, 1, 
        -1,  1,  1,    1, 1, 
        -1, -1,  1,    1, 0, 
         1, -1,  1,    0, 0, 
         1,  1, -1,    0, 1, 
         1,  1,  1,    1, 1, 
         1, -1,  1,    1, 0, 
         1, -1, -1,    0, 0, 
         1, -1, -1,    0, 1, 
         1, -1,  1,    1, 1, 
        -1, -1,  1,    1, 0, 
        -1, -1, -1,    0, 0, 
        -1, -1, -1,    0, 1, 
        -1, -1,  1,    1, 1, 
        -1,  1,  1,    1, 0, 
        -1,  1, -1,    0, 0, 
         1,  1,  1,    0, 1, 
         1,  1, -1,    1, 1, 
        -1,  1, -1,    1, 0, 
        -1,  1,  1,    0, 0
    };

    GLushort indices[] = {
         0,  1,  2,  3,
         4,  5,  6,  7, 
         8,  9, 10, 11,
        12, 13, 14, 15,
        16, 17, 18, 19, 
        20, 21, 22, 23
    };

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, __texture_id_crate);
    glTexCoordPointer(2, GL_SHORT, 5 * sizeof(GLshort), &(vertices[3]));
    glVertexPointer(3, GL_SHORT, 5 * sizeof(GLshort), vertices);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, indices);

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/*
 * The core of the Collision Detection Example.
 *  - Animate the Sphere by moving the X position.
 *  - (Remember to) Update the Sphere "Bounding Box" Object.
 *  - CHECK FOR COLLISION with Left and Right Cube and set new direction.
 */
static void animationHandler (int value) {
    __sphere_x += (GLfloat)value / 3.0;
    gdVector3dInit(&(gdHitSphere(&__sphere)->center), __sphere_x, 0.0f, 0.0f);

    if (gdHitCollision(&__sphere, &__cube_left))
        value = 1;
    else if (gdHitCollision(&__sphere, &__cube_right))
        value = -1;

    glutPostRedisplay();

    glutTimerFunc(ANIMATION_TIMEOUT, animationHandler, value);
}

static void init (void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glShadeModel(GL_SMOOTH);    
    glEnable(GL_DEPTH_TEST);

    /* Setup Textures */
    setupTexture();

    /* Setup Cube Display List */
    __cube_id = glGenLists(1);
    glNewList(__cube_id, GL_COMPILE);
        drawCube();
    glEndList();

    /* Setup Sphere Display List */
    __sphere_id = glGenLists(1);
    glNewList(__sphere_id, GL_COMPILE);
        drawSphere();
    glEndList();

    /* Setup Cube Right Bounding Box, Aprox. */
    gdHitSetBoxType(&__cube_right);
    gdVector3dInit(&(gdHitBox(&__cube_right)->min), 12.0f, 0.0f, 0.0f);
    gdVector3dInit(&(gdHitBox(&__cube_right)->max), 13.0f, 1.0f, 1.0f);

    /* Setup Cube Left Bounding Box, Aprox. */
    gdHitSetBoxType(&__cube_left);
    gdVector3dInit(&(gdHitBox(&__cube_left)->min), -7.0f, 0.0f, 0.0f);
    gdVector3dInit(&(gdHitBox(&__cube_left)->max), -6.0f, 1.0f, 1.0f);

    /* Setup Sphere Bounding Box, Aprox. */
    gdHitSetSphereType(&__sphere);
    gdHitSphere(&__sphere)->radius = 1.0f;
    gdVector3dInit(&(gdHitSphere(&__sphere)->center), 0.0f, 0.0f, 0.0f);    
}

static void displayHandler (void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    /* Setup Camera */
    glTranslatef(0.0f, 0.0f, -16.0f);
    glRotatef(15.0f, 1.0f, 0.0f, 0.0f);     
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);     

    /* Draw Sphere, with __sphere_x Animation Translation */
    glPushMatrix();
        glTranslatef(__sphere_x, 0.0f, 0.0f);
        glCallList(__sphere_id);
    glPopMatrix();

    /* Draw Cube Left */
    glPushMatrix();
        glTranslatef(-7.0f, 0.0f, 0.0f);
        glCallList(__cube_id);
    glPopMatrix();

    /* Draw Cube Right */
    glPushMatrix();
        glTranslatef(13.0f, 0.0f, 0.0f);
        glCallList(__cube_id);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

static void reshapeHandler (int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei)h); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 200.0f);
}

int main (int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);

    glutInitWindowSize(600, 360); 
    glutInitWindowPosition(10, 10);
    
    glutCreateWindow("OpenGL Test Hit");

    init();
    glutDisplayFunc(displayHandler);
    glutReshapeFunc(reshapeHandler);
    glutTimerFunc(ANIMATION_TIMEOUT, animationHandler, 1);

    glutMainLoop();
    return(0);
}

