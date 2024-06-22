#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace utility {
	class Utility
	{
		//METHODS
		public:
			int getRandomNumber(int lowerBound, int upperBound);
			glm::vec3 getRandomVector(int lowerBound[], int upperBound[]);
	};

}

