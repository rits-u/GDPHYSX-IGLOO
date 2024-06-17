#pragma once

#include "MyCamera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace camera {
	class OrthoCamera : public MyCamera
	{
		private:
			float leftMost;
			float rightMost;
			float bottomMost;
			float topMost;

		public:
			OrthoCamera();

		public:
			glm::mat4 giveProjection();
			glm::mat4 giveView();

		public:
			void setPosition(float leftmost, float rightMost, float bottomMost, float topmost);
			void setLeftMost(float leftmost);
			void setRightMost(float rightMost);
			void setTopMost(float topmost);
			void setBottomMost(float bottomMost);


	};
}