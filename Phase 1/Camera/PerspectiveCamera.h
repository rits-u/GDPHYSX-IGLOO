#pragma once

#include "MyCamera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace camera {
	class PerspectiveCamera : public MyCamera
	{
		private:
			float cam_x;
			float cam_y;
			float cam_z;

			glm::vec3 WorldUp;
			glm::vec3 Center;

			float FOV;

		public:
			PerspectiveCamera();

		public:
			// glm::mat4 giveProjection(float width, float height);
			// glm::mat4 giveView(int type);
		
		private:
			glm::vec3 getPosition();
			glm::mat4 getView();
			glm::mat4 getProjection();


		};

}
