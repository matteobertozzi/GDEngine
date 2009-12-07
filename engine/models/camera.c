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

