#pragma once

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../tiny_obj_loader.h"

#include "../P6/MyVector.h"


namespace model{
	using namespace P6;

	class Model3D
	{
		private:
			MyVector position;
			glm::vec3 scale;
			glm::vec3 axis;
			glm::vec3 theta;
			glm::vec4 color;
			std::vector<GLuint> mesh_indices;
			GLuint VAO;
			GLuint shaderProg;
			glm::mat4 projection;
			glm::mat4 viewMatrix;


		public:
			Model3D();
			Model3D(MyVector position, glm::vec3 scale, glm::vec4 color);
			Model3D(MyVector position, glm::vec3 scale, glm::vec4 color, GLuint shaderProg);

		public:
			void loadModel_(std::string objSrc, tinyobj::attrib_t* attributes, GLuint* VBO);
			void bindBuffers_(tinyobj::attrib_t attributes, GLuint* VBO);
			void drawModel_();
			void bindCamera_(glm::mat4 projection, glm::mat4 viewMatrix);

		public:
			void setPosition(MyVector position);
			void setScale(glm::vec3 scale);
			void setColor(glm::vec4 color);
			void setShader(GLuint shaderProg);
			void setCameraProperties(glm::mat4 projection, glm::mat4 viewMatrix);

	};

}