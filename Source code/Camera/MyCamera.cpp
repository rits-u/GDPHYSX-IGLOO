#include "MyCamera.h"
using namespace camera;

//constructor
MyCamera::MyCamera() {
	this->z_far = 1.0f;
	this->z_near = -1.0f;

	this->cameraPos = glm::vec3(/*x_mod*/1.0f, 0.0f,10.0f);
	this->worldUp = glm::vec3(0,1.0f,0);
	this->center = glm::vec3(0,3.0f,0);

	this->F = glm::vec3(this->center - this->cameraPos);
	this->F = glm::normalize(this->F);

	this->R = glm::normalize(glm::cross(F,worldUp));

	this->U = glm::normalize(glm::cross(R,F));

	this->cameraOrientation = glm::mat4(1.0f);

	this->cameraPositionMatrix = glm::translate(glm::mat4(1.0f), this->cameraPos * -1.0f);

	this->cameraOrientation[0][0] = this->R.x;
	this->cameraOrientation[1][0] = this->R.y;
	this->cameraOrientation[2][0] = this->R.z;

	this->cameraOrientation[0][1] = this->U.x;
	this->cameraOrientation[1][1] = this->U.y;
	this->cameraOrientation[2][1] = this->U.z;

	this->cameraOrientation[0][2] = -this->F.x;
	this->cameraOrientation[1][2] = -this->F.y;
	this->cameraOrientation[2][2] = -this->F.z;

	this->viewMatrix = this->cameraOrientation * this->cameraPositionMatrix;

	this->projection = glm::ortho(-800.0f, 800.0f, -800.0f,800.0f, -1.0f, 1000.0f);
}

glm::mat4 MyCamera::getView()
{
	return glm::mat4(1.0f);
}

glm::mat4 MyCamera::giveProjection()
{
	return this->projection;
}