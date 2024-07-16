#include "ParticleSpring.h"

using namespace P6;

ParticleSpring::ParticleSpring(P6Particle* particle, float _springConst, float _restLen) : otherParticle(particle), springConstant(_springConst), restLength(_restLen) {}

void ParticleSpring::UpdateForce(P6Particle* particle, float time)
{
    //Gt current pos of particle
    VectorClass pos = particle->position;

    //use poistion of other particle instead
    //create vecor pos -> other particle
    VectorClass force = pos - otherParticle->position;

    //get mag of vector above
    float mag = force.findMagnitude(force.x,force.y);

    float springForce = -springConstant * abs(mag-restLength);

    //get dir from particle to anchor point
    //idk if correct
    force = force.findDirection(force);

    //apply force using direction above
    force = force * springForce;

    //add force
    particle->AddForce(force);
}

