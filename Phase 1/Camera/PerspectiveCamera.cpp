#include "PerspectiveCamera.h"
using namespace camera;

PerspectiveCamera::PerspectiveCamera() {
    this->cam_x = 0.0f;
    this->cam_y = 0.0f;
    this->cam_z = 1.0f;
    this->cameraPos = glm::vec3(this->cam_x, this->cam_y, this->cam_z);
    this->WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->Center = glm::vec3(0.0f, 0.0f, 0.0f);
    this->FOV = 60.0f;
}

glm::mat4 PerspectiveCamera::giveProjection(float width, float height) {
    return glm::perspective(glm::radians(this->FOV), height / width, this->z_near, this->z_far);
}

glm::mat4 PerspectiveCamera::giveView(int type) {
    return glm::lookAt(this->cameraPos, this->Center, this->WorldUp);
}