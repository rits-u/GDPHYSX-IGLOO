#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace P6 {
	class MyVector
	{
		//FIELDS
	public:
		float x, y, z;

		//CONSTRUCTORS
	public:
		MyVector() : x(0), y(0), z(0) {}
		MyVector(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}

		explicit operator glm::vec3() const { return glm::vec3(x, y, z); }

		//METHODS
	public:
		float getMagnitude();
		float SquareMagnitude();
		MyVector normalize();
		MyVector getDirection();
		MyVector operator+ (const MyVector v);
		void operator+= (const MyVector v);
		MyVector operator- (const MyVector v);
		void operator-= (const MyVector v);

		MyVector operator* (const float f);
		void scalarMultiplication(const float f);
		MyVector operator* (const MyVector v);
		void operator*=(const MyVector v);
		float scalarProduct(const MyVector v);
		MyVector getCrossProduct(const MyVector v);

	};
}

