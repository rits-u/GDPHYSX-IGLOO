#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace model {
	class Camera
	{
		public:
			glm::vec3 center;
			glm::vec3 worldUp;
			float z_near;
			float z_far;

			//ortho
			float leftmost;
			float rightmost;
			float bottommost;
			float topmost;

			//perspective
			float FOV;

		public:
			Camera();
			void bindCamera(std::string camType, float width, float height, float rotate, GLuint shaderProg);
			glm::mat4 getProjection(std::string camType, float width, float height);
			glm::mat4 getView(std::string camType, float rotate);


			



	};

}

