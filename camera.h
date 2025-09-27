#ifndef CAMERA_H
#define CAMERA_H

#include "game_struct.h"

void SetCameraFollowPlayer();
void InterpolateCameraToPos(GameCamera *camera, Vector2 target, float speed, float deltaTime);

#endif