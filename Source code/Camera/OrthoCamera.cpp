#include "OrthoCamera.h"
#include "iostream"
using namespace camera;


OrthoCamera::OrthoCamera() {
	this->leftMost = -800.0f;
	this->rightMost = 800.0f;
	this->topMost = 800.0f;
	this->bottomMost = -800.0f;
	this->z_near = -1.0f;
	this->z_far = 1000.0f;

	this->cameraPos = glm::vec3(0, 0, 0);
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->center = glm::vec3(0.0f, 3.0f, 0.0f);
	this->projection = glm::ortho(this->leftMost, this->rightMost, this->bottomMost, this->topMost, this->z_near, this->z_far);
}

OrthoCamera::OrthoCamera(float leftmost, float rightMost, float bottomMost, float topmost) {
	this->leftMost = leftmost;
	this->rightMost = rightMost;
	this->bottomMost = topmost;
	this->topMost = bottomMost;
	this->z_near = -1.0f;
	this->z_far = 1.0f;
	this->cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->center = glm::vec3(0.0f, 3.0f, 0.0f);
}

//this function returns the view matrix of orthographic camera
glm::mat4 OrthoCamera::giveView() {
	glm::mat4 view = glm::mat4(1.0f);
	return view;
}

//this function returns the projection matrix of orthographic camera
glm::mat4 OrthoCamera::giveProjection() {
	this->z_near = 1000.0f;
	this->z_far = -1000.0f;
	return glm::ortho(this->leftMost, this->rightMost, this->bottomMost, this->topMost, this->z_near, this->z_far);
}

