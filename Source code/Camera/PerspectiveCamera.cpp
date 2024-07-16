#include "PerspectiveCamera.h"
using namespace camera;

PerspectiveCamera::PerspectiveCamera() {
    this->cam_x = 0.0f;
    this->cam_y = 0.0f;
    this->cam_z = 3.0f;
    this->cameraPos = glm::vec3(0, 100.0f, 10.0f);
    this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->center = glm::vec3(0.0f, 0.0f, 0.0f);
    this->FOV = 60.0f;
}

//this function returns the projection matrix of perspective camera
glm::mat4 PerspectiveCamera::giveProjection() {
    this->z_near = 500.0f;
    this->z_far = -500.0f;
    return glm::perspective(glm::radians(this->FOV), 800.0f/800.0f , this->z_near, this->z_far);
}

//this function returns the view matrix of perspective camera
glm::mat4 PerspectiveCamera::giveView(int type) {
    return glm::lookAt(this->cameraPos, this->center, this->worldUp);
}