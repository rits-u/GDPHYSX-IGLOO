#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MyVector.h"

class Renderline
{
    public:
    P6::MyVector P1,P2;
    glm::mat4 ProjectionMatrix;
    GLuint shaderProg;
    P6::MyVector Color = P6::MyVector(1,0,0);

    Renderline(P6::MyVector p1, P6::MyVector p2, GLuint shaderProg);

    void Update(P6::MyVector p1, P6::MyVector p2, glm::mat4 projectionMatrix);

    void Draw();


};