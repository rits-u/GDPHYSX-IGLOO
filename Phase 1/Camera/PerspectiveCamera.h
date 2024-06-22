#pragma once

#include "MyCamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace camera {
	class PerspectiveCamera : public MyCamera
	{

	//FIELDS
	public:
		float cam_x;
		float cam_y;
		float cam_z;
		float FOV;

	//CONSTRUCTOR
	public:
		PerspectiveCamera();

	//METHODS
	public:
		glm::mat4 giveProjection(float width, float height);
		glm::mat4 giveView(int type);

	};

}
