#ifndef _GDENGINE_CAMERA_H_
#define _GDENGINE_CAMERA_H_

#include <GDEngine/Vector3d.h>
#include <GDEngine/Types.h>

typedef struct {
    GDVector3d position;
    GDFloat    yrotation;
    GDFloat    floor;
    GDFloat    theta;
} GDCamera;

void gdCameraInit         (GDCamera *camera);

void gdCameraMoveUp       (GDCamera *camera, GDFloat step);
void gdCameraMoveDown     (GDCamera *camera, GDFloat step);

void gdCameraMoveForward  (GDCamera *camera, GDFloat step);
void gdCameraMoveBackward (GDCamera *camera, GDFloat step);

void gdCameraMoveLeft     (GDCamera *camera, GDFloat step);
void gdCameraMoveRight    (GDCamera *camera, GDFloat step);

void gdCameraDebug        (const GDCamera *camera);

#endif /* !_GDENGINE_CAMERA_H_ */

