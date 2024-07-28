#pragma once

#include "../P6/MyVector.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace utility {
	using namespace P6;

	class RenderLine
	{
	public:
		MyVector P1;
		MyVector P2;
		glm::mat4 ProjectionMatrix;
		//glm::mat4 view;
		MyVector Color;

		RenderLine();
		RenderLine(MyVector P1, MyVector P2, MyVector Color);

		void Update(MyVector p1, MyVector p2, glm::mat4 projectionMatrix);

		//void Update(glm::mat4 projectionMatrix, glm::mat4 view);
		void Draw();
	};

}
