#include "OrthoCamera.h"

using namespace camera;

OrthoCamera::OrthoCamera() {
	this->leftMost = -800.0f;
	this->rightMost = 800.0f;
	this->topMost = 800.0f;
	this->bottomMost = -800.0f;

	this->z_near = -1000.0f;
	this->z_far = 1000.0f;

	this->cameraPos = glm::vec3(0.0f,7.0f,3.0f);
	this->viewEye = glm::mat4(1.0f);
	this->projectionEye = glm::ortho(this->leftMost, this->rightMost, this->bottomMost, this->topMost, this->z_near, this->z_far);
}

glm::vec3 OrthoCamera::getPosition() {return this->cameraPos;}
glm::mat4 OrthoCamera::getView() {return this->viewEye;}
glm::mat4 OrthoCamera::getProjection() {return this->projectionEye;}


// glm::mat4 OrthoCamera::giveView() {
// 	glm::mat4 viewMatrix = glm::mat4(1.0f);
// 	return viewMatrix;
// }

// glm::mat4 OrthoCamera::giveProjection() {
// 	this->z_near = 2000.0f;
// 	this->z_far = -2000.0f;
// 	return glm::ortho(this->leftMost, this->rightMost, this->bottomMost, this->topMost, this->z_near, this->z_far);
// }


// void OrthoCamera::setPosition(float leftmost, float rightMost, float bottomMost, float topmost) {
// 	this->leftMost = leftmost;
// 	this->rightMost = rightMost;
// 	this->bottomMost = bottomMost;
// 	this->topMost = topmost;
// }

// void OrthoCamera::setLeftMost(float leftMost) {
// 	this->leftMost = leftMost;
// }

// void OrthoCamera::setRightMost(float rightMos) {
// 	this->rightMost = rightMos;
// }

// void OrthoCamera::setTopMost(float topmost) {
// 	this->topMost = topMost;
// }

// void OrthoCamera::setBottomMost(float bottomMost) {
// 	this->bottomMost = bottomMost;
// }

