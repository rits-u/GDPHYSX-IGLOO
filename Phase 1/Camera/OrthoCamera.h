#pragma once

#include "MyCamera.h"


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
			// glm::mat4 giveProjection();
			// glm::mat4 giveView();

		public:
			// void setPosition(float leftmost, float rightMost, float bottomMost, float topmost);
			// void setLeftMost(float leftmost);
			// void setRightMost(float rightMost);
			// void setTopMost(float topmost);
			// void setBottomMost(float bottomMost);

		private:
			glm::vec3 getPosition();
			glm::mat4 getView();
			glm::mat4 getProjection();


	};
}