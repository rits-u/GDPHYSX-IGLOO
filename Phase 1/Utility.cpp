#include "Utility.h"
using namespace utility;

int Utility::getRandomNumber(int lowerBound, int upperBound) {
    int offset = lowerBound;
    int range = upperBound - lowerBound + 1;
    int rng = offset + (rand() % range);
    return rng;
}

glm::vec3 Utility::getRandomVector(int lowerBound[], int upperBound[]) {
    glm::vec3 vecRng = {};

    for (int i = 0; i < 3; i++) {
        int offset = lowerBound[i];
        int range = upperBound[i] - lowerBound[i] + 1;

        vecRng[i] = offset + (rand() % range);
    }

    return vecRng;
}