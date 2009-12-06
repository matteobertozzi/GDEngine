#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GDEngine/OpenGL.h>

#include <GDEngine/ModelReader.h>
#include <GDEngine/Camera.h>
#include <GDEngine/Maths.h>
#include <GDEngine/Alloc.h>

#define CAMERA_MOVE_UP_STEP           (4.0f)
#define CAMERA_MOVE_FORwARD_STEP      (10.0f)
#define CAMERA_MOVE_LEFT_STEP         (10.0f)
#define CAMERA2_TRANSLATION_STEP      (5.0f)
#define CAMERA2_ROTATION_STEP         (2.0f)

typedef struct {
    int draw_wireframe;
    unsigned int frame;
    int timebase;
    char fps[16];

    GLuint modelDisplayList;
    GLfloat tx, ty, tz;
    GLfloat rx, ry, rz;
    GDCamera camera;
} AppContext;

static AppContext __appContext = {
    .tx = 0.0f, .ty = 0.0f, .tz = 0.0f,
    .rx = 0.0f, .ry = 0.0f, .rz = 0.0f,

    .draw_wireframe = 0,
    .timebase = 0,
    .frame = 0,
};

static GDBool __initModelTextures (GDUInt index, void *data, void *args) {
    gdOpenGlInitModelTextures(gdModel(data));
    return(GD_FALSE);
}

static GDBool __drawModel (GDUInt index, void *data, void *args) {
    gdOpenGlModelDraw(gdModel(data));
    return(GD_FALSE);
}

static void __loadModels (const char *filename) {
    GDModelReader reader;

    gdModelReaderInit(&reader);
    gdModelReaderRead(&reader, filename);

    /* Initialize Model Textures */
    gdListForeach(reader.models, __initModelTextures, NULL);

    /* Compile Model Display List */
    __appContext.modelDisplayList = glGenLists(1);
    glNewList(__appContext.modelDisplayList, GL_COMPILE);
        gdListForeach(reader.models, __drawModel, NULL);
    glEndList();

    gdModelReaderRelease(&reader);
}

static void init (void) {
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

    glShadeModel(GL_SMOOTH);    

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glPolygonMode(GL_FRONT_AND_BACK, __appContext.draw_wireframe ? GL_LINE : GL_FILL);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Initialize Camera */
    gdCameraInit(&__appContext.camera);
}

static void displayFps (void) {
    int time;
    float tc;

    __appContext.frame++;
    time = glutGet(GLUT_ELAPSED_TIME);        
    if ((tc = (time - __appContext.timebase)) > 1000) {
        float fps = (__appContext.frame * 1000.0f) / tc;
        snprintf(__appContext.fps, 15, "FPS %.2f", fps);

        __appContext.timebase = time;
        __appContext.frame = 0;
    }

    gdOpenGlDrawString(-32.0f, 23.0f, __appContext.fps);
}

static void displayHandler (void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, -60.0f);

    /* Draw Frame per Seconds */
    displayFps();

    /* Setup Camera */
    gdOpenGlSetCamera(&(__appContext.camera));

    /* Setup Second Camera Translation */
    glTranslatef(__appContext.tx, __appContext.ty, __appContext.tz);

    /* Setup Second Camera Rotation */
    glRotatef(__appContext.rx, 1.0f, 0.0f, 0.0f);
    glRotatef(__appContext.ry, 0.0f, 1.0f, 0.0f);
    glRotatef(__appContext.rz, 0.0f, 0.0f, 1.0f);

    /* Draw Model */
    glPushMatrix();
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glCallList(__appContext.modelDisplayList);
        //fprintf(stderr, "OpenGL: %s\n", gluErrorString(glGetError()));
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

static void reshapeHandler (int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei)h); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 20480.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void specialHandler (int key, int x, int y) {
    if (key == GLUT_KEY_PAGE_UP) {
        gdCameraMoveUp(&(__appContext.camera), CAMERA_MOVE_UP_STEP);
    } else if (key == GLUT_KEY_PAGE_DOWN) {
        gdCameraMoveDown(&(__appContext.camera), CAMERA_MOVE_UP_STEP);
    } else if (key == GLUT_KEY_UP) {
        gdCameraMoveForward(&(__appContext.camera), CAMERA_MOVE_FORwARD_STEP);
    } else if (key == GLUT_KEY_DOWN) {
        gdCameraMoveBackward(&(__appContext.camera), CAMERA_MOVE_FORwARD_STEP);
    } else if (key == GLUT_KEY_LEFT) {
        gdCameraMoveLeft(&(__appContext.camera), CAMERA_MOVE_LEFT_STEP);
    } else if (key == GLUT_KEY_RIGHT) {
        gdCameraMoveRight(&(__appContext.camera), CAMERA_MOVE_LEFT_STEP);
    }

    glutPostRedisplay();
}

void keyboardHandler (unsigned char key, int x, int y) {
    if (key == 'w') {
        __appContext.draw_wireframe = !__appContext.draw_wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, __appContext.draw_wireframe ? GL_LINE : GL_FILL);
    } else if (key == 'x') {
        __appContext.rx = gdMathWrapDegAngle(__appContext.rx + CAMERA2_ROTATION_STEP);
    } else if (key == 'y') {
        __appContext.ry = gdMathWrapDegAngle(__appContext.ry + CAMERA2_ROTATION_STEP);
    } else if (key == 'z') {
        __appContext.rz = gdMathWrapDegAngle(__appContext.rz + CAMERA2_ROTATION_STEP);
    } else if (key == 'i') {
        __appContext.tz += CAMERA2_TRANSLATION_STEP;
    } else if (key == 'o') {
        __appContext.tz -= CAMERA2_TRANSLATION_STEP;
    } else if (key == 'l') {
        __appContext.tx -= CAMERA2_TRANSLATION_STEP;
    } else if (key == 'r') {
        __appContext.tx += CAMERA2_TRANSLATION_STEP;
    } else if (key == 'u') {
        __appContext.ty -= CAMERA2_TRANSLATION_STEP;
    } else if (key == 'd') {
        __appContext.ty += CAMERA2_TRANSLATION_STEP;
    } else if (key == 'p') {
        printf("STATE\n");
        printf(" - T %.2f %.2f %.2f\n", __appContext.tx, __appContext.ty, __appContext.tz);
        printf(" - R %.2f %.2f %.2f\n", __appContext.rx, __appContext.ry, __appContext.rz);
        gdCameraDebug(&(__appContext.camera));
    }
        
    glutPostRedisplay();
}

void idleHandler (void) {
    glutPostRedisplay();
}

int main (int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);

    glutInitWindowSize(800, 600); 
    glutInitWindowPosition(10, 10);
    
    glutCreateWindow("OpenGL View Model");

    if (argc > 1)
        __loadModels(argv[1]);

    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));

    init();
    glutIdleFunc(idleHandler);
    glutDisplayFunc(displayHandler);
    glutReshapeFunc(reshapeHandler);
    glutSpecialFunc(specialHandler);
    glutKeyboardFunc(keyboardHandler);

    glutMainLoop();
    return(0);
}

