#include "OrthoCamera.h"
using namespace camera;

OrthoCamera::OrthoCamera() {
	this->leftMost = -1.0f;
	this->rightMost = 1.0f;
	this->topMost = 1.0f;
	this->bottomMost = -1.0f;
	this->z_near = -1.0f;
	this->z_far = 1.0f;
}


glm::mat4 OrthoCamera::giveView() {
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	return viewMatrix;
}

glm::mat4 OrthoCamera::giveProjection() {
	this->z_near = 2000.0f;
	this->z_far = -2000.0f;
	return glm::ortho(this->leftMost, this->rightMost, this->bottomMost, this->topMost, this->z_near, this->z_far);
}


void OrthoCamera::setPosition(float leftmost, float rightMost, float bottomMost, float topmost) {
	this->leftMost = leftmost;
	this->rightMost = rightMost;
	this->bottomMost = bottomMost;
	this->topMost = topmost;
	
}

void OrthoCamera::setLeftMost(float leftMost) {
	this->leftMost = leftMost;
}

void OrthoCamera::setRightMost(float rightMos) {
	this->rightMost = rightMos;
}

void OrthoCamera::setTopMost(float topmost) {
	this->topMost = topMost;
}

void OrthoCamera::setBottomMost(float bottomMost) {
	this->bottomMost = bottomMost;
}

