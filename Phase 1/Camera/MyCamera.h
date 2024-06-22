#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace camera {
	class MyCamera
	{

	//FIELDS
	public:
		float z_far;
		float z_near;
		glm::vec3 cameraPos;
		glm::vec3 worldUp;
		glm::vec3 center;

	//CONSTRUCTOR
	public:
		MyCamera();

	};

}