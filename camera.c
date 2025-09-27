#include "camera.h"

void SetCameraFollowPlayer();

void InterpolateCameraToPos(GameCamera *camera, Vector2 target, float speed, float deltaTime){
    Vector2 camVec = (Vector2){camera->camera.target.x, camera->camera.target.y};
    camVec = Vector2Lerp(camVec, target, speed * deltaTime);
    camera->camera.target.x = camVec.x;
    camera->camera.target.y = camVec.y;
}