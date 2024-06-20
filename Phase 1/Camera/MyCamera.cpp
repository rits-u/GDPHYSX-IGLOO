#include "MyCamera.h"
using namespace camera;

MyCamera::MyCamera() {
	this->z_far = 1.0f;
	this->z_near = -1.0f;

	this->cameraPos = glm::vec3(0.0f,0.0f,10.0f);
	this->viewEye = glm::mat4();
	this->projectionEye = glm::mat4();
}

void MyCamera::set_zFar(float z_far) {
	this->z_far = z_far;
}

void MyCamera::set_zNear(float z_near) {
	this->z_near = z_near;
}

glm::vec3 MyCamera::getPosition() 
{
	return this->cameraPos;
}
glm::mat4 MyCamera::getView() 
{
	return this->viewEye;
}
glm::mat4 MyCamera::getProjection() 
{
	return this->projectionEye;
}