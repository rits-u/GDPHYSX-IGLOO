#include "AnchoredSpring.h"

using namespace P6;

AnchoredSpring::AnchoredSpring(MyVector pos, float _springConst, float _restLen) : anchorPoint(pos), springConstant(_springConst), restLength(_restLen) {}


void AnchoredSpring::UpdateForce(P6Particle* particle, float time)
{
    //Get current position of particle
        MyVector pos = particle->Position;

        //Vector Pos->anchorpoint
        MyVector force = pos - anchorPoint;

        //create magnitude of vector above
        float mag = force.getMagnitude();

        //
        float springForce = -springConstant * abs(mag - restLength);

        //get dir from the particle to anchor point
        //idk if correct
        //force = force.getDirection();
        force = force.normalize();

        //apply force using direction above
        force = force * springForce;

        //add froce!
        particle->AddForce(force);
}
