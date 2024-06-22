#include "Utility.h"
using namespace utility;

//this function is used for generating a random single number
int Utility::getRandomNumber(int lowerBound, int upperBound) {
    int offset = lowerBound;
    int range = upperBound - lowerBound + 1;
    int rng = offset + (rand() % range);
    return rng;
}

//this function generates a random number three times, respectively as x, y, z
//as the components of a vector
glm::vec3 Utility::getRandomVector(int lowerBound[], int upperBound[]) {
    glm::vec3 vecRng = {};

    for (int i = 0; i < 3; i++) {
        int offset = lowerBound[i];
        int range = upperBound[i] - lowerBound[i] + 1;

        vecRng[i] = offset + (rand() % range);
    }

    return vecRng;
}