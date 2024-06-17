#include "MyCamera.h"
using namespace camera;

MyCamera::MyCamera() {
	this->z_far = 1.0f;
	this->z_near = -1.0f;
}

void MyCamera::set_zFar(float z_far) {
	this->z_far = z_far;
}

void MyCamera::set_zNear(float z_near) {
	this->z_near = z_near;
}