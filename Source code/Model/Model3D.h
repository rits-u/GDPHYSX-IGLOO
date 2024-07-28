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
		//FIELDS
		public:
			MyVector position;
			glm::vec3 scale;
			glm::vec3 axis;
			glm::vec3 theta;
			glm::vec4 color = glm::vec4(1,0,0,0);
			std::vector<GLuint> mesh_indices;
			GLuint VAO;
			GLuint shaderProg;
			glm::mat4 projection;
			glm::mat4 viewMatrix;

		//CONSTRUCTOR
		public:
			Model3D();
			Model3D(glm::vec3 scale, glm::vec4 color, GLuint shaderProg);

		//METHODS
		public:
			void loadModel(std::string objSrc, GLuint* VBO);
			void drawModel();
			
		private:
			void bindBuffers(tinyobj::attrib_t attributes, GLuint* VBO);
			void bindCamera(glm::mat4 projection, glm::mat4 viewMatrix);

		//GETTERS AND SETTERS
		public:
			void setPosition(MyVector position);
			void setScale(glm::vec3 scale);
			void setColor(glm::vec4 color);
			void setShader(GLuint shaderProg);
			void setCameraProperties(glm::mat4 projection, glm::mat4 viewMatrix);

			float getPosition(); //FOR DEBUG ONLY

	};

}