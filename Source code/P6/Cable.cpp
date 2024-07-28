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

       // float mag = force.getMagnitude();

      // float springForce = -100 * abs(mag - cableLength);

        //force = force.normalize();

        //force = force * springForce;

       if (pos.y <= cableLength)
    {
        std::cout << "hello" << std::endl;
        return;
    }
        else particle->AddForce(force);
 

}

float Cable::getCableLength()
{
    return this->cableLength;
}

// ParticleContact* Cable::GetContact()
// {
//     float currLen = getCableLength();

//     if (currLen == length)
//     {
//         return nullptr;
//     }

//       //create contact
//     ParticleContact* ret = new ParticleContact();

//     ret->particles[0] = particles[0];
//     ret->particles[1] = particles[1];

//     //get direction of the contact
//     MyVector dir = particles[1]->Position - particles[0]->Position;

//     //idk if correct
//     dir = dir.getDirection();

//     //if current length > set length of the rod
//     if (currLen > length)
//     {
//         ret->contactNormal = dir;

//         //depth must always be positive to resolve interpenetration
//         ret->depth = currLen - length;
//     }

//     //if curr len is shorter than length of rod
//     else 
//     {
//         //invert the direction
//         ret->contactNormal = dir * -1;

//         //depth must always be positive to resolve interpenetration
//         ret->depth = length - currLen;
//     }

//     //set restitution, always set this to 0 for rods
//     ret->restitution = restitution;

//     //return the contact
//     return ret;
// }