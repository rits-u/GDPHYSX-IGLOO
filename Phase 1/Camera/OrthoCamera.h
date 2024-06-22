#pragma once

#include "MyCamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace camera {
	class OrthoCamera : public MyCamera
	{
	
	//FIELDS
	public:
		float leftMost;
		float rightMost;
		float bottomMost;
		float topMost;

	//CONSTRUCTORS
	public:
		OrthoCamera();
		OrthoCamera(float leftmost, float rightMost, float bottomMost, float topmost);

	//METHODS
	public:
		glm::mat4 giveProjection();
		glm::mat4 giveView();

	};
}