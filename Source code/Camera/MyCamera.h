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
		glm::vec3 F,R,U;
		glm::mat4 cameraPositionMatrix;
		glm::mat4 cameraOrientation;
		glm::mat4 viewMatrix;
		glm::mat4 projection;

	//CONSTRUCTOR
	public:
		MyCamera();

	//GETTER AND SETTERS
	public:
		glm::mat4 getView();
		glm::mat4 giveProjection();

	};

}