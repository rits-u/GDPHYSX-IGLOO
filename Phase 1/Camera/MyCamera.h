#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace camera {
	class MyCamera
	{
	protected:
		float z_far;
		float z_near;

		glm::vec3 cameraPos;
		glm::mat4 viewEye;
		glm::mat4 projectionEye;

	public:
		MyCamera();

	public:
		void set_zFar(float z_far);
		void set_zNear(float z_near);


	public:
		//virtual voids for camera switching
		virtual glm::vec3 getPosition();
		virtual glm::mat4 getView();
		virtual glm::mat4 getProjection();
	};
}
