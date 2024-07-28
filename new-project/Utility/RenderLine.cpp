#include "RenderLine.h"
using namespace utility;

RenderLine::RenderLine() {
	this->P1 = MyVector(0, 0, 0);
	this->P2 = MyVector(0, 0, 0);
	this->ProjectionMatrix = glm::mat4(1);
	this->Color = MyVector(1, 1, 1);
}

RenderLine::RenderLine(MyVector P1, MyVector P2, MyVector Color) {
	this->P1 = P1;
	this->P2 = P2;
	this->ProjectionMatrix = glm::mat4(1);
	this->Color = Color;
}


void RenderLine::Update(MyVector p1, MyVector p2, glm::mat4 projectionMatrix) {
	this->P1 = p1;
	this->P2 = p2;
	this->ProjectionMatrix = projectionMatrix;
}

//void RenderLine::Update(glm::mat4 projectionMatrix, glm::mat4 view) {
//		P1 = p1;
//		P2 = p2;
//	this->ProjectionMatrix = projectionMatrix;
//	this->view = view;
//}

void RenderLine::Draw() {
	glUseProgram(0);

	glm::vec4 d1 = this->ProjectionMatrix * glm::vec4(P1.x, P1.y, P1.z, 1.0f);

	glm::vec4 d2 = this->ProjectionMatrix * glm::vec4(P2.x, P2.y, P2.z, 1.0f);


	glm::vec4 test1 = this->ProjectionMatrix * glm::vec4(0, 0, 0, 1.f);
	glm::vec4 test2 = this->ProjectionMatrix * glm::vec4(1, 1, 1, 1.f);

//	glm::vec4 test1 = this->view * this->ProjectionMatrix * glm::vec4(0, 0, 0, 1.f);
//	glm::vec4 test2 = this->view * this->ProjectionMatrix * glm::vec4(1, 1, 1, 1.f);

	glBegin(GL_LINES);
	glVertex3f(d1.x, d1.y, d1.z);
	glVertex3f(d2.x, d2.y, d2.z);

//	glVertex3f(test1.x, test1.y, test1.z);
	//glVertex3f(test2.x, test2.y, test2.z);

	glEnd();
}