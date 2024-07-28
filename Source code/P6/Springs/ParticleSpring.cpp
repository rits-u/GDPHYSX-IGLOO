#include "ParticleSpring.h"

using namespace P6;

ParticleSpring::ParticleSpring(P6Particle* particle, float _springConst, float _restLen) : otherParticle(particle), springConstant(_springConst), restLength(_restLen) {}

void ParticleSpring::UpdateForce(P6Particle* particle, float time)
{
    //Gt current pos of particle
    MyVector pos = particle->Position;

    //use poistion of other particle instead
    //create vecor pos -> other particle
    MyVector force = pos - otherParticle->Position;

    //get mag of vector above
    float mag = force.getMagnitude();

    float springForce = -springConstant * abs(mag-restLength);

    //get dir from particle to anchor point
    //force = force.getDirection();
    force = force.normalize();

    //apply force using direction above
    force = force * springForce;

    //add force
    particle->AddForce(force);
}

