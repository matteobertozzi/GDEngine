#include "camera.h"
#include "maths.h"

void gdCameraInit (GDCamera *camera) {
    gdVector3dInit(&(camera->position), 0.0f, 0.0f, 0.0f);
    camera->yrotation = 0.0f;
    camera->floor = 0.0f;
    camera->theta = 0.0f;
}

void gdCameraMoveUp (GDCamera *camera, GDFloat step) {
    camera->floor -= step;
}

void gdCameraMoveDown (GDCamera *camera, GDFloat step) {
    camera->floor += step;
}


void gdCameraMoveForward(GDCamera *camera, GDFloat step) {
    GDFloat rad = gdMathDegToRad(camera->yrotation);
    camera->position.x -= gdMathSin(rad) * step;
    camera->position.z -= gdMathCos(rad) * step;
    camera->theta = gdMathWrapDegAngle(camera->theta + 10.0f);
    camera->position.y = gdMathSin(gdMathDegToRad(camera->theta));
}

void gdCameraMoveBackward (GDCamera *camera, GDFloat step) {
    GDFloat rad = gdMathDegToRad(camera->yrotation);
    camera->position.x += gdMathSin(rad) * step;
    camera->position.z += gdMathCos(rad) * step;
    camera->theta = gdMathWrapDegAngle(camera->theta - 10.0f);
    camera->position.y = gdMathSin(gdMathDegToRad(camera->theta));
}


void gdCameraMoveLeft (GDCamera *camera, GDFloat step) {
    camera->yrotation += step;
}

void gdCameraMoveRight(GDCamera *camera, GDFloat step) {
    camera->yrotation -= step;
}

void gdCameraDebug (const GDCamera *camera) {
    printf("CAMERA:\n");
    printf(" - Position: %.2f %.2f %.2f\n", camera->position.x, camera->position.y, camera->position.z);
    printf(" - YRotation: %.2f\n", camera->yrotation);
    printf(" - Floor: %.2f\n", camera->floor);
    printf(" - Theta: %.2f\n", camera->theta);
}

