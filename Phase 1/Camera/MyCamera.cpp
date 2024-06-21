#include "MyCamera.h"
using namespace camera;

//CONSTRUCTOR
MyCamera::MyCamera() {
	this->z_far = 1.0f;
	this->z_near = -1.0f;

	this->cameraPos = glm::vec3(0.0f,0.0f,10.0f);
	this->viewEye = glm::mat4();
	this->projectionEye = glm::mat4();
}

//setter for z_far 
void MyCamera::set_zFar(float z_far) {
	this->z_far = z_far;
}

//setter for z_near 
void MyCamera::set_zNear(float z_near) {
	this->z_near = z_near;
}

//getter for camera position
glm::vec3 MyCamera::getPosition() 
{
	return this->cameraPos;
}

//getter for view matrix
glm::mat4 MyCamera::getView() 
{
	return this->viewEye;
}

//getter for projection matrix
glm::mat4 MyCamera::getProjection() 
{
	return this->projectionEye;
}