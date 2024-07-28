#include "Camera.h"
using namespace model;

Camera::Camera() {
	this->center = glm::vec3(0.f, 0.f, 0.f);
	this->worldUp = glm::vec3(0.f, 1.0f, 0.f);
	this->z_near = -100.f;
	this->z_far = 100.f;

	//ortho
	this->leftmost = -400.f;
	this->rightmost = 400.f;
	this->bottommost = -400.f;
	this->topmost = 400.f;

	//perspective
	this->FOV = 60.f;
}

void Camera::bindCamera(std::string camType, float width, float height, float rotate, GLuint shaderProg) {
	glm::mat4 projection = this->getProjection(camType, width, height);
	glm::mat4 view = this->getView(camType, rotate);

	glUseProgram(shaderProg);

	unsigned int projLoc = glGetUniformLocation(shaderProg, "projection");
	glUniformMatrix4fv(projLoc,  
		1,       
		GL_FALSE,
		glm::value_ptr(projection)); 

	unsigned int viewLoc = glGetUniformLocation(shaderProg, "view");
	glUniformMatrix4fv(viewLoc,  
		1,       
		GL_FALSE,
		glm::value_ptr(view)); 
}

glm::mat4 Camera::getProjection(std::string camType, float width, float height) {
	glm::mat4 projection = glm::mat4(1);

	if (camType == "Ortho") {
		this->z_near = -height;
		this->z_far = height;
		projection = glm::ortho(this->leftmost, this->rightmost, this->bottommost, this->topmost, this->z_near, this->z_far);
	}
	else {
		this->z_near = 100.1f;
		this->z_far = -100.f;
		projection = glm::perspective(glm::radians(this->FOV), height / width, this->z_near, this->z_far);
	}

	return projection;
}

glm::mat4 Camera::getView(std::string camType, float rotate) {
	glm::mat4 view = glm::mat4(1);

	const float radius = 10.0f;
	//float camX = sin(glfwGetTime()) * radius;
	//float camZ = cos(glfwGetTime()) * radius;
	float camX = sin(rotate) * radius;
	float camZ = cos(rotate) * radius;

	if (camType == "Ortho") {
		// viewMatrix1 = glm::lookAt(glm::vec3(0, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		view = glm::lookAt(glm::vec3(camX, 0, camZ), this->center, this->worldUp);

	}
	else {
		view = glm::lookAt(glm::vec3(camX, 0, camZ+500), this->center, this->worldUp);
	}

	return view;
}