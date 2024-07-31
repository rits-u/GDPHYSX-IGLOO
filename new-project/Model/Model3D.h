#pragma once

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include "../tiny_obj_loader.h"

#include "../P6/MyVector.h"


namespace model {
	using namespace P6;

	class Model3D
	{

		//FIELDS
		public:
			MyVector position;
			MyVector scale;
			glm::vec3 axis;
			glm::vec3 theta;
			glm::vec4 color;
			std::vector<GLuint> mesh_indices;
			GLuint VAO;
			GLuint shaderProg;

		//CONSTRUCTOR
		public:
			Model3D();
			Model3D(glm::vec4 color, GLuint shaderProg);
			Model3D(MyVector scale, glm::vec4 color, GLuint shaderProg);

		//METHODS
		public:
			void loadModel(std::string objSrc, GLuint* VBO);
			void drawModel();
			void setScale(MyVector scale);

		private:
			void bindBuffers(tinyobj::attrib_t attributes, GLuint* VBO);

	};

}