#include "PerspectiveCamera.h"
using namespace camera;

PerspectiveCamera::PerspectiveCamera() {
    this->cam_x = 0.0f;
    this->cam_y = 40.0f;
    this->cam_z = 90.0f;

    this->WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    this->Center = glm::vec3(0.0f, 3.0f, 0.0f);
    //this->Center = glm::vec3(0.0f, 0.0f, 0.0f);
    this->FOV = 60.0f;

    this->z_near = 0.1f;
    this->z_far = 100.0f;

    this->cameraPos = glm::vec3(this->cam_x, this->cam_y, this->cam_z);
    this->viewEye = glm::lookAt(this->cameraPos, this->Center, this->WorldUp);
    this->projectionEye = glm::perspective(glm::radians(this->FOV), 800.0f / 800.0f, this->z_near, this->z_far);
}

// glm::mat4 PerspectiveCamera::giveProjection(float width, float height) {
//     return glm::perspective(glm::radians(this->FOV), height / width, this->z_near, this->z_far);
// }

// glm::mat4 PerspectiveCamera::giveView(int type) {
//     return glm::lookAt(this->cameraPos, this->Center, this->WorldUp);
// }


glm::vec3 PerspectiveCamera::getPosition() {return this->cameraPos;}
glm::mat4 PerspectiveCamera::getView() {return this->viewEye;}
glm::mat4 PerspectiveCamera::getProjection() {return this->projectionEye;}