#include "Rod.h"

using namespace P6;

ParticleContact* Rod::GetContact()
{
    //get the current length
    float currLen = CurrentLength();

    //if current length is the same as the set length do nothing
    if (currLen == length)
    {
        return nullptr;
    }

    //create contact
    ParticleContact* ret = new ParticleContact();

    ret->particles[0] = particles[0];
    ret->particles[1] = particles[1];

    //get direction of the contact
    MyVector dir = particles[1]->Position - particles[0]->Position;

    //idk if correct
    dir = dir.getDirection();

    //if current length > set length of the rod
    if (currLen > length)
    {
        ret->contactNormal = dir;

        //depth must always be positive to resolve interpenetration
        ret->depth = currLen - length;
    }

    //if curr len is shorter than length of rod
    else 
    {
        //invert the direction
        ret->contactNormal = dir * -1;

        //depth must always be positive to resolve interpenetration
        ret->depth = length - currLen;
    }

    //set restitution, always set this to 0 for rods
    ret->restitution = restitution;

    //return the contact
    return ret;
}