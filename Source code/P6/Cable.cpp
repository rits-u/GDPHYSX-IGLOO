#include "Cable.h"

using namespace P6;

Cable::Cable(float cableLength)
{
    this->cableLength = cableLength;
}

/*Intially drops the balls down*/
void Cable::UpdateForce(P6Particle* particle, float time)
{
    MyVector pos = particle->Position;
    MyVector force = pos - handlePoint;

    float mag = force.getMagnitude();

    float springForce = -10 * abs(mag - cableLength);

    force = force.normalize();

    force = force * springForce;

    particle->AddForce(force);
       if (pos.y <= cableLength)
    {
        std::cout << "hello" << std::endl;
        return;
    }
}

float Cable::getCableLength()
{
    return this->cableLength;
}